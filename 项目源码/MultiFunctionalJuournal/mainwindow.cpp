#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>
#include<QIODevice>
#include<QSettings>
#include<QInputDialog>
#include<QStringMatcher>
#include<QFormLayout>
#include<QDateTimeEdit>
#include<QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentCategory("默认") //初始化为默认
    , currentCategoryId(-1)
    , currentNoteId(-1)
{
    ui->setupUi(this);
    this->resize(800,600);
    this->setWindowTitle("多功能日志");
    ui->stackedWidget->setCurrentWidget(ui->page);

    // 初始化警报定时器
    alertTimer = new QTimer(this);
    connect(alertTimer, &QTimer::timeout, this, &MainWindow::checkDeadlines);
    alertTimer->start(60 * 1000); // 每分钟检查一次

    //初始化数据库处理器
    dbManager = new DatabaseManager(this);

    dbManager->cleanDuplicateHealthData();

    //初始化分类列表
    initCategoryList();

    connect(ui->noteList, &QListWidget::itemDoubleClicked, this, &MainWindow::on_noteList_itemDoubleClicked);
    //dbManager->testDatabase();

    ui->searchEdit->setPlaceholderText("请输入搜索关键字");
    ui->searchEditText->setPlaceholderText("请输入搜索关键字");
    searchTimer.setSingleShot(true);
    connect(ui->searchEdit,&QLineEdit::textEdited,this,&MainWindow::filterList);
    connect(&searchTimer,&QTimer::timeout,this,[this](){
        performFilter(ui->searchEdit->text());
    });

    searchTimer_text.setSingleShot(true);
    connect(ui->searchEditText,&QLineEdit::textEdited,this,&MainWindow::filterList_text);
    connect(&searchTimer_text,&QTimer::timeout,this,[this](){
        performFilter_text(ui->searchEditText->text());
    });

    account_list_model = new QStandardItemModel(this);
    account_list_model->setHorizontalHeaderLabels({"日期", "分类", "金额", "备注"});
    ui->tableView_account->setModel(account_list_model);
    ui->tableView_account->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QFile file("accounts.csv");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        while(!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList data = line.split(",");
            if(data.size() == 4) {
                QList<QStandardItem*> items;
                for(const QString& str : data) {
                    items << new QStandardItem(str);
                }
                account_list_model->appendRow(items);
            }
        }
        QSettings settings("MyCompany", "AccountApp");
        currentBudget = settings.value("budget", 1000.0).toDouble();
        calculateUsedAmount();
        double remaining = currentBudget - usedAmount;

        QString displayText = QString("预设额度: %1元\n已使用: %2元\n剩余: %3元")
                                  .arg(currentBudget, 0, 'f', 2)
                                  .arg(usedAmount, 0, 'f', 2)
                                  .arg(remaining, 0, 'f', 2);

        ui->label_budget_display->setText(displayText);

        double percentage = (currentBudget > 0) ? (remaining / currentBudget) * 100 : 0;

        if (percentage < 20) {
            ui->label_budget_display->setStyleSheet("color: red; font-weight: bold;");
        } else if (percentage < 50) {
            ui->label_budget_display->setStyleSheet("color: orange;");
        } else {
            ui->label_budget_display->setStyleSheet("color: green;");
        }
    }

    // 初始化待办模型
    todoModel = new QStandardItemModel(this);
    todoModel->setHorizontalHeaderLabels({"完成", "任务内容", "预估用时(时)","截止时间"});
    ui->tableView->setModel(todoModel);

    // 设置列宽
    ui->tableView->setColumnWidth(0, 60);   // 复选框列固定宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // 任务内容自动拉伸
    ui->tableView->setColumnWidth(3, 150);  // 时间列固定宽度

    // 加载待办数据
    QFile todoFile("todos.csv");
    if(todoFile.open(QIODevice::ReadOnly)) {
        QTextStream todoStream(&todoFile);
        todoStream.readLine(); // 跳过CSV表头

        while(!todoStream.atEnd()) {
            QString line = todoStream.readLine();
            QStringList data = line.split(",");

            if(data.size() >= 4) {
                QList<QStandardItem*> rowItems;
                // 复选框列（转换0/1为状态）
                QStandardItem *checkItem = new QStandardItem();
                checkItem->setCheckable(true);
                checkItem->setCheckState(data[0].toInt() ? Qt::Checked : Qt::Unchecked);
                // 任务内容列
                QStandardItem *taskItem = new QStandardItem(data[1]);
                QStandardItem *estimatedItem = new QStandardItem(data[2]);
                // 截止时间列
                QStandardItem *timeItem = new QStandardItem(data[3]);

                rowItems << checkItem << taskItem <<estimatedItem<< timeItem;
                todoModel->appendRow(rowItems);
            }
        }
        todoFile.close();
    } else {
        qDebug() << "待办数据文件打开失败：" << todoFile.errorString();
    }

    initHealthPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化分类列表
void MainWindow::initCategoryList()
{
    loadCategoriesFromDatabase();

    // 如果数据库中没有分类，添加默认分类
    if (ui->categoryList->count() == 0) {
        QStringList defaultCategories = {"默认", "工作", "个人", "学习"};
        foreach (const QString &category, defaultCategories) {
            dbManager->addCategory(category);
        }
        loadCategoriesFromDatabase();
    }
}


//从数据库加载分类表
void MainWindow::loadCategoriesFromDatabase()
{
    // 清空当前列表
    ui->categoryList->clear();

    // 从数据库获取所有分类
    QStringList categories = dbManager->getALLCategories();

    // 添加到列表
    ui->categoryList->addItems(categories);
}

void MainWindow::on_actionNew_File_triggered()
{
    //ui->textEdit->clear();
    //ui->textEdit->setText(QString());

    setWindowTitle(("记事本"));
    ui->stackedWidget->setCurrentWidget(ui->page_chooseClass);
}



void MainWindow::on_actionSave_triggered()
{
    QString filename;
    if(filename.isEmpty()){
        filename=QFileDialog::getSaveFileName(this,"Save");
    }
    QFile file(filename);
    if(!file.open(QFile::Text|QIODevice::WriteOnly)){
        QMessageBox::warning(this,"警告","无法打开此文件："+file.errorString());
        return;
    }
    QTextStream fout(&file);
    QString text=ui->textEdit->toPlainText();
    fout<<text;
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString filename;
    filename=QFileDialog::getSaveFileName(this,"Save");
    QFile file(filename);
    if(!file.open(QFile::Text|QIODevice::WriteOnly)){
        QMessageBox::warning(this,"警告","无法打开此文件："+file.errorString());
        return;
    }
    QTextStream fout(&file);
    QString text=ui->textEdit->toPlainText();
    fout<<text;
    file.close();
}



void MainWindow::on_actioncut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionAbout_triggered()
{

}


void MainWindow::on_actionopen_triggered()
{
    QString filename=QFileDialog::getOpenFileName(this,"打开文件");
    QFile file(filename);
    if(!file.open(QFile::Text|QIODevice::ReadOnly)){
        QMessageBox::warning(this,"警告","无法打开此文件："+file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream fin(&file);
    QString text=fin.readAll();
    ui->textEdit->setText(text);
    file.close();
}

//转到记事本
void MainWindow::on_pushButton_clicked()
{
    //转到分类界面
    setWindowTitle("记事本");
    ui->stackedWidget->setCurrentWidget(ui->page_chooseClass);
}

//返回主界面
void MainWindow::on_actionHome_triggered()
{
    setWindowTitle(("多功能日志"));
    ui->stackedWidget->setCurrentWidget(ui->page);
}

//新增分类
void MainWindow::on_addBtn_clicked()
{
    //添加按钮，将line edit内容转到list widget
    //检查分类名称是否已存在
    QString newClass = ui->categoryEdit->text();

    if(dbManager->categoryExists(newClass)){
        QMessageBox::warning(this, "错误", "分类名称已存在");
        return;
    }
    if(!newClass.isEmpty()){
        //添加至数据库
        if(dbManager->addCategory(newClass)){
            loadCategoriesFromDatabase();
            ui->categoryEdit->clear();
        }
        else{
            QMessageBox::warning(this,"错误", "分类添加失败");
        }
    }
    /*
    if(!ui->categoryEdit->text().isEmpty()){
        ui->categoryList->addItem(ui->categoryEdit->text());
        ui->categoryEdit->clear();
    }
    //保存
    saveCategories();
    */
}

//双击分类
void MainWindow::on_categoryList_itemDoubleClicked(QListWidgetItem *item)
{
    //选择分类，进入分类详情界面
    currentCategory = item->text();
    currentCategoryId = dbManager->getCategoryId(currentCategory);
    if (currentCategoryId == -1) {
        QMessageBox::warning(this, "错误", "获取分类ID失败");
        return;
    }

    //加载分类笔记
    loadNotesForCurrentCategory();

    ui->stackedWidget->setCurrentWidget(ui->page_classDetail);
    //这里修改了窗口标题，返回home时会改回
    setWindowTitle(currentCategory + " - 笔记列表 - 记事本");
}

//加载当前分类下的笔记
void MainWindow::loadNotesForCurrentCategory()
{
    ui->noteList->clear();

    //获取分类下所有笔记
    QStringList notes = dbManager->getNotesByCategory(currentCategoryId);

    //添加到笔记列表
    foreach(const QString &note, notes){
        QStringList parts = note.split(";");
        if(parts.size() == 2){
            QString id = parts[0];
            QString title = parts[1];
            QListWidgetItem *item = new QListWidgetItem(title);
            item->setData(Qt::UserRole, id.toInt());
            ui->noteList->addItem(item);
        }
    }
}


//选择分类并删除
void MainWindow::on_deleteBtn_clicked()
{
    QList<QListWidgetItem*> selectedItems = ui->categoryList->selectedItems();
    if (selectedItems.isEmpty()){
        QMessageBox::information(this, "提示", "请先选择要删除的分类");
        return;
    }
    foreach(QListWidgetItem* item, selectedItems){
        if(item->text() == "默认"){
            QMessageBox::warning(this, "警告！", "不可删除'默认'分类！");
            return;
        }
    }

    QMessageBox::StandardButton reply1;
    reply1 = QMessageBox::question(this, "确认删除", "确定要删除选中的分类吗？", QMessageBox::Yes|QMessageBox::No);
    //删除
    if(reply1 == QMessageBox::Yes){
        foreach(QListWidgetItem* item, selectedItems){
            if(item->text() == currentCategory){
                currentCategory.clear();
            }
            //从数据库删除
            dbManager->deleteCategory(item->text());
        }
        //刷新分类表
        loadCategoriesFromDatabase();
    }
}

//删除全部分类
void MainWindow::on_deleteAllClassBtn_clicked()
{
    //检查有没有可删除的分类
    if(ui->categoryList->count() == 0){
        QMessageBox::information(this, "提示", "没有可删除的分类");
        return;
    }
    //警告对话框
    QMessageBox::StandardButton replyall;
    replyall = QMessageBox::warning(this, "警告！", "这将删除所有分类,仅保留默认分类，且不可恢复！\n确定要继续吗？", QMessageBox::Yes|QMessageBox::No);
    //删除
    if(replyall == QMessageBox::Yes){
        //分类清空
        if(dbManager->deleteAllCategories()){
            //ui更新
            ui->categoryList->clear();
            ui->categoryList->addItems({"默认"});
            //当前分类清空
            currentCategory = "默认";
            QMessageBox::information(this, "完成", "删除操作已完成");
        }
        else{
            QMessageBox::critical(this, "错误", "删除分类失败,请稍后重试");
        }
    }
}

//编辑分类
void MainWindow::on_editClassBtn_clicked()
{
    QListWidgetItem *item = ui->categoryList->currentItem();
    if(!item){
        QMessageBox::information(this, "提示", "请先选择要编辑的分类");
        return;
    }
    QString oriName = item->text();//原名称

    if(oriName == "默认"){
        QMessageBox::warning(this, "警告!", "不可重命名'默认'分类！");
        return;
    }
    bool ok;
    QString newName = QInputDialog::getText(this, "重命名分类", "请输入新的分类名称：", QLineEdit::Normal, oriName, &ok);
    if(ok && !newName.isEmpty() && newName != oriName){
        if(dbManager->categoryExists(newName)){
            QMessageBox::warning(this, "错误", "分类名称已存在");
            return;
        }

        if(dbManager->updateCategory(oriName, newName)){
            if(oriName == currentCategory){
                currentCategory = newName;
            }
            loadCategoriesFromDatabase();
        }
        else{
            QMessageBox::warning(this, "错误", "更新分类失败");
        }
    }
}

//选中笔记并进入编辑界面
void MainWindow::on_noteList_itemDoubleClicked(QListWidgetItem *item)
{
    currentNoteId = item->data(Qt::UserRole).toInt();
    QString content = dbManager->getNoteContent(currentNoteId);

    ui->titleEdit->setText(item->text());
    ui->textEdit->setText(content);

    ui->stackedWidget->setCurrentWidget(ui->page_txt);
    setWindowTitle(currentCategory + " - " + item->text() + " - 记事本");
}

//新建笔记
void MainWindow::on_newNoteBtn_clicked()
{
    currentNoteId = -1;//表示新建
    ui->titleEdit->clear();
    ui->textEdit->clear();
    ui->stackedWidget->setCurrentWidget(ui->page_txt);
    setWindowTitle(currentCategory + " - 新建笔记 - 记事本");
}

//编辑选中的笔记
void MainWindow::on_editNoteBtn_clicked()
{
    QListWidgetItem *item = ui->noteList->currentItem();
    if (!item) {
        QMessageBox::information(this, "提示", "请选择要编辑的笔记");
        return;
    }
    //加载
    currentNoteId = item->data(Qt::UserRole).toInt();
    QString content = dbManager->getNoteContent(currentNoteId);

    ui->titleEdit->setText(item->text());
    ui->textEdit->setText(content);

    ui->stackedWidget->setCurrentWidget(ui->page_txt);
    setWindowTitle(currentCategory + " - " + item->text() + " - 记事本");
}

//删除选中的笔记
void MainWindow::on_deleteNoteBtn_clicked()
{
    QListWidgetItem *item = ui->noteList->currentItem();
    if (!item) {
        QMessageBox::information(this, "提示", "请选择要删除的笔记");
        return;
    }
    int noteId = item->data(Qt::UserRole).toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除", "确定要删除笔记 '" + item->text() + "' 吗？",QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        if(dbManager->deleteNote(noteId)){
            delete ui->noteList->takeItem(ui->noteList->row(item));
            QMessageBox::information(this, "成功", "笔记已删除");
        }
        else{
            QMessageBox::warning(this, "错误", "笔记删除失败");
        }
    }
}

//从分类对应笔记界面回到分类选择
void MainWindow::on_backToCategoryBtn_clicked()
{
    setWindowTitle("记事本");
    ui->stackedWidget->setCurrentWidget(ui->page_chooseClass);
}

//笔记编辑界面保存并退出
void MainWindow::on_fileSaveBtn_clicked()
{
    QMessageBox::StandardButton reply0;
    reply0 = QMessageBox::question(this, "确认保存", "确定要保存这篇笔记吗？", QMessageBox::Yes|QMessageBox::No);
    if(reply0 == QMessageBox::No){
        return;
    }

    QString title = ui->titleEdit->text();
    if (title.isEmpty()) {
        QMessageBox::warning(this, "警告", "笔记标题不能为空");
        return;
    }
    QString content = ui->textEdit->toPlainText();

    if(currentNoteId == -1){
        //新建
        int newNoteId = dbManager->addNote(currentCategoryId, title, content);
        if(newNoteId != -1){
            QMessageBox::information(this, "成功", "笔记已保存");
            currentNoteId = newNoteId;
            //返回分类详情
            loadNotesForCurrentCategory();
            ui->stackedWidget->setCurrentWidget(ui->page_classDetail);
            setWindowTitle(currentCategory + " - 笔记列表 - 记事本");
        }
        else{
            QMessageBox::warning(this, "错误", "笔记保存失败");
        }
    }
    else{
        //直接更新笔记
        if (dbManager->updateNote(currentNoteId, title, content)) {
            QMessageBox::information(this, "成功", "笔记已更新");
            // 返回分类详情页
            loadNotesForCurrentCategory();
            ui->stackedWidget->setCurrentWidget(ui->page_classDetail);
            setWindowTitle(currentCategory + " - 笔记列表 - 记事本");
        }
        else {
            QMessageBox::warning(this, "错误", "笔记更新失败");
        }
    }
}

//笔记编辑界面直接退出
void MainWindow::on_quitEditBtn_clicked()
{
    QMessageBox::StandardButton reply1;
    reply1 = QMessageBox::warning(this, "确认退出", "确定要退出并返回至分类详情页吗？", QMessageBox::Yes|QMessageBox::No);
    if(reply1 == QMessageBox::Yes){
        loadNotesForCurrentCategory();
        ui->stackedWidget->setCurrentWidget(ui->page_classDetail);
        setWindowTitle(currentCategory + " - 笔记列表 - 记事本");
    }
}


void MainWindow::on_backToHomePageBtn_clicked()
{
    setWindowTitle("多功能日志");
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void MainWindow::filterList(const QString &filtertext){
    if(filtertext.isEmpty()){
        searchTimer.stop();
        for(int i=0;i<ui->categoryList->count();++i){
            ui->categoryList->item(i)->setHidden(false);
        }
        ui->statusLabel->setText("已清除关键词并显示所有分类");
        return;
    }
    searchTimer.start(300);
}

//搜索对应关键词的项，分类
void MainWindow::performFilter(const QString &filtertext){
    int visible_count=0;
    const int totalitems=ui->categoryList->count();
    QStringMatcher matcher(filtertext,Qt::CaseInsensitive);
    for(int i=0;i<totalitems;++i){
        QListWidgetItem *item=ui->categoryList->item(i);
        QString itemtext=item->text();
        bool match=false;
        match=(matcher.indexIn(itemtext)!=-1);
        item->setHidden(!match);
        if(match){
            visible_count++;
        }
    }
    QString statusMessage=QString("共找到 %1/%2 个匹配的项").arg(visible_count).arg(totalitems);
    ui->statusLabel->setText(statusMessage);
}
//清除关键词，分类界面
void MainWindow::on_clearButton_clicked()
{
    ui->searchEdit->clear();
    ui->statusLabel->setText("已清除关键词并显示所有分类");
    for(int i=0;i<ui->categoryList->count();++i){
        ui->categoryList->item(i)->setHidden(false);
    }
}

//清除关键词，笔记选择界面
void MainWindow::on_clearButtonText_clicked()
{
    ui->searchEditText->clear();
    ui->statusLabelText->setText("已清除关键词并显示所有分类");
    for(int i=0;i<ui->noteList->count();++i){
        ui->noteList->item(i)->setHidden(false);
    }
}

void MainWindow::filterList_text(const QString &filtertext){
    if(filtertext.isEmpty()){
        searchTimer_text.stop();
        for(int i=0;i<ui->noteList->count();++i){
            ui->noteList->item(i)->setHidden(false);
        }
        ui->statusLabelText->setText("已清除关键词并显示所有分类");
        return;
    }
    searchTimer_text.start(300);
}
//搜索关键词对应笔记
void MainWindow::performFilter_text(const QString &filtertext){
    int visible_count=0;
    const int totalitems=ui->noteList->count();
    QStringMatcher matcher(filtertext,Qt::CaseInsensitive);
    for(int i=0;i<totalitems;++i){
        QListWidgetItem *item=ui->noteList->item(i);
        QString itemtext=item->text();
        int noteid=dbManager->getNoteId(currentCategoryId,itemtext);
        QString itemcontent=dbManager->getNoteContent(noteid);
        bool match=false;
        match=((matcher.indexIn(itemtext)!=-1)||(matcher.indexIn(itemcontent)!=-1));
        item->setHidden(!match);
        if(match){
            visible_count++;
        }
    }
    QString statusMessage=QString("共找到 %1/%2 个匹配的项").arg(visible_count).arg(totalitems);
    ui->statusLabelText->setText(statusMessage);
}
//进入记账界面
void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_accounting);
     setWindowTitle("记账");
}
//返回主界面按钮
void MainWindow::on_pushButton_back_clicked()
{
    on_pushButton_saveAccount_clicked();
    ui->stackedWidget->setCurrentWidget(ui->page);
     setWindowTitle("多功能日志");
}
//添加记账条目
void MainWindow::on_pushButton_new_clicked()
{
    QDialog dlg(this);
    dlg.setWindowTitle("添加记账条目");

    QFormLayout *form = new QFormLayout(&dlg);

    QLineEdit *amountEdit = new QLineEdit();
    QDoubleValidator *validator = new QDoubleValidator(0, 1000000, 2, this);
    amountEdit->setValidator(validator);
    QComboBox *categoryCombo = new QComboBox();
    categoryCombo->addItems({"餐饮", "交通", "购物", "娱乐", "医疗", "教育", "其他"});
    categoryCombo->setEditable(true);
    QLineEdit *remarkEdit = new QLineEdit();
    QDateTimeEdit *timeEdit = new QDateTimeEdit(QDateTime::currentDateTime().addDays(0));

    timeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    timeEdit->setCalendarPopup(true);

    form->addRow("金额：", amountEdit);
    form->addRow("分类：",categoryCombo);
    form->addRow("时间：", timeEdit);
    form->addRow("备注：",remarkEdit);

    QDialogButtonBox btnBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addRow(&btnBox);
    QObject::connect(&btnBox, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(&btnBox, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    if (dlg.exec() == QDialog::Accepted && !amountEdit->text().isEmpty()){
        QString amount=amountEdit->text();
        QString time = timeEdit->dateTime().toString("yyyy-MM-dd HH:mm");
        QString remark=remarkEdit->text();
        QString category=categoryCombo->currentText();


        if(!ui->tableView_account->model()) {
            on_pushButton_3_clicked();
        }

        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_account->model());

        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(time);
        rowItems << new QStandardItem(category);
        rowItems << new QStandardItem(amount);
        rowItems << new QStandardItem(remark);

        model->appendRow(rowItems);
        ui->tableView_account->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->tableView_account->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        ui->tableView_account->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
        ui->tableView_account->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

        updateBudgetDisplay();
    }
}

//保存账本条目
void MainWindow::on_pushButton_saveAccount_clicked()
{
    QMessageBox::StandardButton replyall;
    replyall = QMessageBox::question(this, "确认保存", "确定要保存吗？", QMessageBox::Yes|QMessageBox::No);
    if(replyall == QMessageBox::No){
        return;
    }
    QFile file("accounts.csv");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        for(int row = 0; row < account_list_model->rowCount(); ++row) {
            QStringList rowData;
            for(int col = 0; col < account_list_model->columnCount(); ++col) {
                rowData << account_list_model->item(row, col)->text();
            }
            stream << rowData.join(",") << "\n";
        }
        QMessageBox::information(this, "成功", "账本已更新");
        updateBudgetDisplay();
    }
    else{
        QMessageBox::warning(this, "错误", "账本更新失败");
    }
}

//删除对应账本条目
void MainWindow::on_pushButton_delete_clicked()
{
    QModelIndexList selected = ui->tableView_account->selectionModel()->selectedRows();

    if (selected.isEmpty()) {
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  "确定要删除选中的记录吗？",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_account->model());
        std::sort(selected.begin(), selected.end(), [](const QModelIndex &a, const QModelIndex &b) {
            return a.row() > b.row();
        });

        for (const QModelIndex &index : selected) {
            model->removeRow(index.row());
        }
        QFile file("accounts.csv");
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            for(int row = 0; row < account_list_model->rowCount(); ++row) {
                QStringList rowData;
                for(int col = 0; col < account_list_model->columnCount(); ++col) {
                    rowData << account_list_model->item(row, col)->text();
                }
                stream << rowData.join(",") << "\n";
            }
        }
        updateBudgetDisplay();
    }
}

//清除账本条目
void MainWindow::on_pushButton_clear_clicked()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_account->model());

    if (!model || model->rowCount() == 0) {
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认清除",
                                  "确定要清除所有记账条目吗？此操作不可恢复！",
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        model->removeRows(0, model->rowCount());
        QFile file("accounts.csv");
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            for(int row = 0; row < account_list_model->rowCount(); ++row) {
                QStringList rowData;
                for(int col = 0; col < account_list_model->columnCount(); ++col) {
                    rowData << account_list_model->item(row, col)->text();
                }
                stream << rowData.join(",") << "\n";
            }
        }
        QMessageBox::information(this, "完成", "所有记账条目已清除");
        updateBudgetDisplay();
    }
}

//编辑预设额度
void MainWindow::on_pushButton_edit_clicked()
{
    bool ok;
    double newBudget = QInputDialog::getDouble(this, "编辑预设额度","请输入新的预设额度:",currentBudget, 0.0,1000000.0,2,&ok);

    if (ok) {
        currentBudget = newBudget;

        QSettings settings("MyCompany", "AccountApp");
        settings.setValue("budget", currentBudget);

        updateBudgetDisplay();

        QMessageBox::information(this, "成功", "预设额度已更新");
    }
}

//计算总开销
void MainWindow::calculateUsedAmount()
{
    double new_usedAmount = 0.0;
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView_account->model());

    if (model) {
        for (int row = 0; row < model->rowCount(); ++row) {
            QStandardItem *amountItem = model->item(row, 2);
            if (amountItem) {
                bool ok;
                double amount = amountItem->text().toDouble(&ok);
                if (ok) {
                    new_usedAmount += amount;
                }
            }
        }
    }
    if(new_usedAmount!=usedAmount){
        usedAmount=new_usedAmount;
        warningShowed=false;
    }
}

//更新账本显示
void MainWindow::updateBudgetDisplay()
{
    calculateUsedAmount();
    double remaining = currentBudget - usedAmount;

    QString displayText = QString("预设额度: %1元\n已使用: %2元\n剩余: %3元")
                              .arg(currentBudget, 0, 'f', 2)
                              .arg(usedAmount, 0, 'f', 2)
                              .arg(remaining, 0, 'f', 2);

    ui->label_budget_display->setText(displayText);

    double percentage = (currentBudget > 0) ? (remaining / currentBudget) * 100 : 0;

    if (percentage < 20) {
        ui->label_budget_display->setStyleSheet("color: red; font-weight: bold;");
    } else if (percentage < 50) {
        ui->label_budget_display->setStyleSheet("color: orange;");
    } else {
        ui->label_budget_display->setStyleSheet("color: green;");
    }

    if(!warningShowed){
        if(percentage<0){
            QMessageBox::warning(this, "预算预警", "您的支出已超过预算，请注意控制支出！！！");
        }
        else if (percentage < 10) {
            QMessageBox::warning(this, "预算预警", "您的剩余额度不足10%，请注意控制支出！！");
        }
        else if (percentage < 20) {
            QMessageBox::warning(this, "预算预警", "您的剩余额度不足20%，请注意控制支出！");
        }
        else if (percentage<50){
            QMessageBox::warning(this,"预算预警","您的剩余额度已不足一半，请注意控制支出");
        }
        warningShowed=true;
    }
}
//前往待办界面
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_todo); // 跳转到待办页面
    setWindowTitle("待办");
}
//添加待办事项
void MainWindow::on_btnAdd_clicked()
{
    QDialog dlg(this);
    dlg.setWindowTitle("添加待办事项");

    QFormLayout *form = new QFormLayout(&dlg);

    QLineEdit *taskEdit = new QLineEdit();
    QLineEdit *estimatedEdit = new QLineEdit();
    QDateTimeEdit *timeEdit = new QDateTimeEdit(QDateTime::currentDateTime().addDays(1));
    timeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    timeEdit->setCalendarPopup(true);

    // 添加表单行
    form->addRow("任务内容：", taskEdit);
    form->addRow("预估时间（时）",estimatedEdit);
    form->addRow("截止时间：", timeEdit);

    QDialogButtonBox btnBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addRow(&btnBox);

    // 连接按钮信号
    QObject::connect(&btnBox, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(&btnBox, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    if (dlg.exec() == QDialog::Accepted && !taskEdit->text().isEmpty()) {
        QString task = taskEdit->text();
        QString estimated=estimatedEdit->text();
        QString deadline = timeEdit->dateTime().toString("yyyy-MM-dd HH:mm");
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());

        if (!model) {
            model = new QStandardItemModel(this);
            // 修改表头为三列
            model->setHorizontalHeaderLabels({"完成", "任务内容", "预估时间（时）","截止时间"});
            ui->tableView->setModel(model);
            // 设置列宽参数
            ui->tableView->setColumnWidth(0, 60);
            ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        }

        QList<QStandardItem*> rowItems;
        //新增复选框列
        QStandardItem *checkItem = new QStandardItem();
        checkItem->setCheckable(true);
        checkItem->setCheckState(Qt::Unchecked);
        rowItems << checkItem;
        rowItems << new QStandardItem(task);
        rowItems << new QStandardItem(estimated);
        rowItems << new QStandardItem(deadline);

        model->appendRow(rowItems);

        // 固定第一列宽度
        ui->tableView->setColumnWidth(0, 60);
        // 第二列自动拉伸
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        // 第三列根据内容自动调整
        ui->tableView->resizeColumnToContents(2);
        ui->tableView->resizeColumnToContents(3);
        // 设置第三列最小宽度保证显示完整
        if (ui->tableView->columnWidth(3) < 150) {
            ui->tableView->setColumnWidth(3, 150);
        }
    }
}
//保存待办
void MainWindow::on_btnSaveTodo_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "确认保存",
        "确定要保存当前待办列表吗？",
        QMessageBox::Yes | QMessageBox::No
        );

    if(reply == QMessageBox::No) return;

    QFile file("todos.csv");
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "错误", "无法打开待办数据文件");
        return;
    }

    QTextStream stream(&file);
    stream << "完成状态,任务内容,截止时间\n"; // CSV表头

    for(int row = 0; row < todoModel->rowCount(); ++row) {
        QStringList rowData;
        // 复选框状态（0/1）
        rowData << QString::number(todoModel->item(row, 0)->checkState() == Qt::Checked ? 1 : 0);
        // 任务内容
        rowData << todoModel->item(row, 1)->text();
        // 截止时间
        rowData << todoModel->item(row, 2)->text();
        rowData << todoModel->item(row, 3)->text();

        stream << rowData.join(",") << "\n";
    }

    QMessageBox::information(this, "成功", "待办列表已保存");
}
// 删除选中待办项
void MainWindow::on_btnDeleteTodo_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if(selected.isEmpty()) {
        QMessageBox::information(this, "提示", "请先选择要删除的待办项");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "确认删除",
        QString("确定要删除选中的%1项待办吗？").arg(selected.size()),
        QMessageBox::Yes | QMessageBox::No
        );

    if(reply == QMessageBox::Yes) {
        // 按反向顺序删除避免行号变化
        std::sort(selected.begin(), selected.end(), [](const QModelIndex &a, const QModelIndex &b){
            return a.row() > b.row();
        });

        foreach(const QModelIndex &index, selected) {
            todoModel->removeRow(index.row());
        }
    }
}

//代办临期检测与提醒
void MainWindow::checkDeadlines()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
    if(!model || model->rowCount() == 0) return;

    const int alertMinutes = 30; // 提前30分钟提醒
    QStringList alerts;
    const QDateTime current = QDateTime::currentDateTime();

    for(int row = 0; row < model->rowCount(); ++row) {
        // 完成状态检查
        QStandardItem *checkItem = model->item(row, 0);
        if(checkItem && checkItem->checkState() == Qt::Checked) {
            continue; // 已完成的任务跳过提醒
        }


        QStandardItem *timeItem = model->item(row, 3); // 第3列是截止时间
        if(!timeItem) continue;

        QDateTime deadline = QDateTime::fromString(timeItem->text(), "yyyy-MM-dd HH:mm");
        if(!deadline.isValid()) continue;

        qint64 secondsLeft = current.secsTo(deadline);
        if(secondsLeft > 0 && secondsLeft <= alertMinutes * 60) {
            QStandardItem *taskItem = model->item(row, 1); // 第2列是任务内容
            QString alertMsg = QString("待办提醒：%1\n剩余时间：%2分钟")
                                   .arg(taskItem ? taskItem->text() : "未命名任务")
                                   .arg(qCeil(secondsLeft / 60.0)); // 向上取整更安全
            alerts << alertMsg;
        }
    }

    if(!alerts.isEmpty()) {
        QMessageBox::information(this,
                                 "待办事项提醒",
                                 alerts.join("\n\n"),
                                 QMessageBox::Ok);
    }
}

//从待办返回主界面
void MainWindow::on_pushButton_5_clicked()
{
    on_btnSaveTodo_clicked();
    ui->stackedWidget->setCurrentWidget(ui->page);
    setWindowTitle("多功能日志");
}

//待办事项排序
void MainWindow::on_pushButton_6_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"确认排序","确定要使用推荐待办事项顺序吗？",QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Todo_sort();
    }
}
//排序的函数实现
void MainWindow::Todo_sort(){
    if (!todoModel || todoModel->rowCount() == 0)
        return;

    struct TodoTask {
        int originalIndex;
        double timeNeeded;
        QDateTime deadline;
        QList<QStandardItem*> items;
        double priority;

        bool operator==(const TodoTask& other) const {
            return originalIndex == other.originalIndex;
        }
    };

    QVector<TodoTask> tasks;
    const QDateTime currentTime = QDateTime::currentDateTime();

    for (int row = 0; row < todoModel->rowCount(); ++row) {
        if (todoModel->item(row, 0)->checkState() == Qt::Checked)
            continue;

        QStandardItem* timeItem = todoModel->item(row, 3);
        QStandardItem* estimateItem = todoModel->item(row, 2);

        if (!timeItem || !estimateItem) continue;

        QDateTime deadline = QDateTime::fromString(timeItem->text(), "yyyy-MM-dd HH:mm");
        if (!deadline.isValid()) continue;

        bool ok;
        double hours = estimateItem->text().toDouble(&ok);
        if (!ok || hours <= 0) continue;

        TodoTask task;
        task.originalIndex = row;
        task.timeNeeded = hours;
        task.deadline = deadline;

        for (int col = 0; col < todoModel->columnCount(); ++col) {
            QStandardItem* origItem = todoModel->item(row, col);
            QStandardItem* newItem = new QStandardItem();
            newItem->setText(origItem->text());
            if(col==0){
                newItem->setCheckable(origItem->isCheckable());
                newItem->setCheckState(origItem->checkState());
            }
            task.items.append(newItem);
        }

        double hoursLeft = currentTime.secsTo(deadline) / 3600.0;
        double urgency = (hoursLeft > 0) ? std::min((1.0 / hoursLeft),999.9) : 1000.0;
        task.priority = urgency + 1/hours;

        tasks.append(task);
    }

    std::sort(tasks.begin(), tasks.end(), [](const TodoTask& a, const TodoTask& b) {
        return a.priority > b.priority;
    });

    QVector<TodoTask> optimizedOrder;
    QSet<int> addedIndices;
    double totalTimeUsed = 0.0;

    for (auto& task : tasks) {
        double hoursLeft = currentTime.secsTo(task.deadline) / 3600.0 - totalTimeUsed;

        if (hoursLeft >= task.timeNeeded) {
            optimizedOrder.append(task);
            addedIndices.insert(task.originalIndex);
            totalTimeUsed += task.timeNeeded;
        }
    }

    QVector<TodoTask> remainingTasks;
    for (auto& task : tasks) {
        if (!addedIndices.contains(task.originalIndex)) {
            remainingTasks.append(task);
        }
    }

    std::sort(remainingTasks.begin(), remainingTasks.end(),
              [](const TodoTask& a, const TodoTask& b) {
                  return a.deadline < b.deadline;
              });

    optimizedOrder.append(remainingTasks);

    QStandardItemModel* newModel = new QStandardItemModel(this);
    newModel->setHorizontalHeaderLabels({"完成", "任务内容", "预估时间（时）", "截止时间"});
    for (const auto& task : optimizedOrder) {
        newModel->appendRow(task.items);
    }

    for (int row = 0; row < todoModel->rowCount(); ++row) {
        if (todoModel->item(row, 0)->checkState() == Qt::Checked) {
            QList<QStandardItem*> rowItems;
            for (int col = 0; col < todoModel->columnCount(); ++col) {
                QStandardItem* origItem = todoModel->item(row, col);
                QStandardItem* newItem = new QStandardItem();
                newItem->setText(origItem->text());
                if(col==0){
                    newItem->setCheckable(origItem->isCheckable());
                    newItem->setCheckState(origItem->checkState());
                }
                rowItems.append(newItem);
            }
            newModel->appendRow(rowItems);
        }
    }

    ui->tableView->setModel(newModel);

    if (todoModel) {
        QObject::disconnect(todoModel, nullptr, this, nullptr);
        delete todoModel;
    }

    todoModel = newModel;

    ui->tableView->setColumnWidth(0, 60);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(3);
    if (ui->tableView->columnWidth(3) < 150) {
        ui->tableView->setColumnWidth(3, 150);
    }
}

//跳转到运动健康
void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_health_and_exercise); // 跳转到运动健康页面
    setWindowTitle("运动与健康");
}

//返回主界面
void MainWindow::on_back_to_menuBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    setWindowTitle("多功能日志");
}

//初始化运动健康
void MainWindow::initHealthPage()
{
    // 静态变量用于确保只初始化一次
    static bool modelsInitialized = false;

    if (!modelsInitialized) {
        // 初始化食物表格模型 - 只执行一次
        foodModel = new QStandardItemModel(this);
        foodModel->setHorizontalHeaderLabels({"名称", "热量 (kcal)", "单位", "类型"});

        // 初始化运动表格模型 - 只执行一次
        exerciseModel = new QStandardItemModel(this);
        exerciseModel->setHorizontalHeaderLabels({"名称", "每小时消耗 (kcal)", "类型"});

        // 设置表格视图 - 只执行一次
        ui->tableView_food->setModel(foodModel);
        ui->tableView_food->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_food->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView_food->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView_food->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        ui->tableView_exercise->setModel(exerciseModel);
        ui->tableView_exercise->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_exercise->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView_exercise->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView_exercise->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        modelsInitialized = true;
    }

    // 每次进入健康页面都刷新数据
    refreshFoodList();
    refreshExerciseList();

    // 初始化日期为今天 - 每次进入页面都更新
    ui->logDateEdit->setDate(QDate::currentDate());

    // 更新热量显示 - 每次进入页面都更新
    updateCalorieDisplay();
}

// 刷新食物表格
void MainWindow::refreshFoodList()
{
    if (!foodModel) return; // 安全保护

    // 清除现有数据（保留表头）
    foodModel->removeRows(0, foodModel->rowCount());

    QList<FoodItem> foods = dbManager->getAllFoodItems(true);

    for (const FoodItem& food : foods) {
        QList<QStandardItem*> rowItems;

        // 名称
        QStandardItem *nameItem = new QStandardItem(food.name);
        nameItem->setData(food.id, Qt::UserRole); // 存储ID
        rowItems << nameItem;

        // 热量
        QStandardItem *calorieItem = new QStandardItem(QString::number(food.calories));
        calorieItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        rowItems << calorieItem;

        // 单位
        rowItems << new QStandardItem(food.unit);

        // 类型
        rowItems << new QStandardItem(food.isCustom ? "自定义" : "系统");

        foodModel->appendRow(rowItems);
    }
}

// 刷新运动表格
void MainWindow::refreshExerciseList()
{
    if (!exerciseModel) return; // 安全保护

    // 清除现有数据（保留表头）
    exerciseModel->removeRows(0, exerciseModel->rowCount());

    QList<ExerciseItem> exercises = dbManager->getAllExerciseItems(true);

    for (const ExerciseItem& exercise : exercises) {
        QList<QStandardItem*> rowItems;

        // 名称
        QStandardItem *nameItem = new QStandardItem(exercise.name);
        nameItem->setData(exercise.id, Qt::UserRole); // 存储ID
        rowItems << nameItem;

        // 每小时消耗
        QStandardItem *calorieItem = new QStandardItem(QString::number(exercise.caloriesPerHour));
        calorieItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        rowItems << calorieItem;

        // 类型
        rowItems << new QStandardItem(exercise.isCustom ? "自定义" : "系统");

        exerciseModel->appendRow(rowItems);
    }
}

// 添加自定义食物
void MainWindow::on_addFoodBtn_clicked()
{
    QString name = ui->foodNameEdit->text().trimmed();
    double calories = ui->foodCaloriesSpin->value();
    QString unit = ui->foodUnitEdit->text().trimmed();

    // 提前验证输入
    if (name.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "食物名称不能为空");
        return;
    }

    if (unit.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "食物单位不能为空");
        return;
    }

    if (calories <= 0) {
        QMessageBox::warning(this, "输入错误", "热量值必须大于0");
        return;
    }

    // 检查名称是否已存在
    QList<FoodItem> foods = dbManager->getAllFoodItems(true);
    for (const FoodItem& food : foods) {
        if (food.name == name) {
            QMessageBox::warning(this, "输入错误", "该食物名称已存在");
            return;
        }
    }

    // 保存到数据库
    if (dbManager->addCustomFood(name, calories, unit)) {
        // 刷新表格
        refreshFoodList();
        // 清空输入
        ui->foodNameEdit->clear();
        ui->foodCaloriesSpin->setValue(100);
        ui->foodUnitEdit->clear();
        QMessageBox::information(this, "成功", "食物添加成功");
    } else {
        QMessageBox::critical(this, "错误", "添加食物失败");
    }
}


//记录饮食条目
void MainWindow::on_logFoodBtn_clicked()
{
    QModelIndexList selected = ui->tableView_food->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "错误", "请选择一个食物");
        return;
    }
    //获取选中食物的id
    int row = selected.first().row();
    int foodId = foodModel->item(row, 0)->data(Qt::UserRole).toInt();
    double quantity = ui->foodQuantitiesSpin->value();
    QDate date = ui->logDateEdit->date();

    if(quantity <= 0){
        QMessageBox::warning(this, "输入错误", "请输入有效的质量/数量");
        return;
    }
    if(dbManager->logFoodConsumption(foodId, quantity, date)){
        ui->foodQuantitiesSpin->setValue(0);
        updateCalorieDisplay();
        QMessageBox::information(this, "成功", "饮食记录已保存");
    }else{
        QMessageBox::critical(this, "错误", "记录保存失败");
    }
}

// 添加自定义运动
void MainWindow::on_addExerciseBtn_clicked()
{
    QString name = ui->exerciseNameEdit->text().trimmed();
    double calories = ui->exerciseCaloriesSpin->value();

    // 提前验证输入
    if (name.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "运动名称不能为空");
        return;
    }

    if (calories <= 0) {
        QMessageBox::warning(this, "输入错误", "消耗热量必须大于0");
        return;
    }

    // 检查名称是否已存在
    QList<ExerciseItem> exercises = dbManager->getAllExerciseItems(true);
    for (const ExerciseItem& exercise : exercises) {
        if (exercise.name == name) {
            QMessageBox::warning(this, "输入错误", "该运动名称已存在");
            return;
        }
    }

    // 保存到数据库
    if (dbManager->addCustomExercise(name, calories)) {
        // 刷新表格
        refreshExerciseList();
        // 清空输入
        ui->exerciseNameEdit->clear();
        ui->exerciseCaloriesSpin->setValue(300);
        QMessageBox::information(this, "成功", "运动添加成功");
    } else {
        QMessageBox::critical(this, "错误", "添加运动失败");
    }
}

//记录运动
void MainWindow::on_logExerciseBtn_clicked()
{
    QModelIndexList selected = ui->tableView_exercise->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "错误", "请选择一项运动");
        return;
    }
    //获取选中运动ID
    int row = selected.first().row();
    int exerciseId = exerciseModel->item(row, 0)->data(Qt::UserRole).toInt();
    double duration = ui->exerciseDurationSpin->value();
    QDate date = ui->logDateEdit->date();

    if(duration <= 0){
        QMessageBox::warning(this, "输入错误", "请输入有效的时长");
        return;
    }
    if(dbManager->logExercise(exerciseId, duration, date)){
        ui->exerciseDurationSpin->setValue(0);
        updateCalorieDisplay();
        QMessageBox::information(this, "成功", "运动记录已保存");
    }else{
        QMessageBox::critical(this, "错误", "记录保存失败");
    }
}

//更新热量显示
void MainWindow::updateCalorieDisplay()
{
    QDate date = ui->logDateEdit->date();
    DailyCalories data = dbManager->getDailyCalories(date);
    ui->intakeLabel->setText(QString("摄入: %1 kcal").arg(data.intake));
    ui->expenditureLabel->setText(QString("消耗: %1 kcal").arg(data.expenditure));

    double balance = data.intake - data.expenditure;
    QString balanceText = QString("总收支: %1 kcal").arg(balance);

    // 设置样式
    if (balance > 0) {
        ui->balanceLabel->setText("<font color='red'>" + balanceText + " (盈余)</font>");
    } else if (balance < 0) {
        ui->balanceLabel->setText("<font color='green'>" + balanceText + " (亏损)</font>");
    } else {
        ui->balanceLabel->setText(balanceText);
    }
}

// 日期变化时更新显示
void MainWindow::onLogDateChanged(const QDate &date)
{
    Q_UNUSED(date);
    updateCalorieDisplay();
}



//删除自定义食物
void MainWindow::on_deleteFoodBtn_clicked()
{
    QModelIndexList selected = ui->tableView_food->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "错误", "请选择要删除的食物");
        return;
    }

    int row = selected.first().row();
    int foodId = foodModel->item(row, 0)->data(Qt::UserRole).toInt();
    QString foodName = foodModel->item(row, 0)->text();

    // 检查是否为自定义食物
    if (foodModel->item(row, 3)->text() != "自定义") {
        QMessageBox::warning(this, "错误", "只能删除自定义食物");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  "确定要删除食物 '" + foodName + "' 吗？",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 从数据库中删除
        if (dbManager->deleteFoodItem(foodId)) {
            // 从模型中删除
            foodModel->removeRow(row);
            QMessageBox::information(this, "成功", "食物已删除");
        } else {
            QMessageBox::critical(this, "错误", "删除失败");
        }
    }
}

//删除自定义运动
void MainWindow::on_deleteExerciseBtn_clicked()
{
    QModelIndexList selected = ui->tableView_exercise->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "错误", "请选择要删除的运动");
        return;
    }

    int row = selected.first().row();
    int exerciseId = exerciseModel->item(row, 0)->data(Qt::UserRole).toInt();
    QString exerciseName = exerciseModel->item(row, 0)->text();

    // 检查是否为自定义运动
    if (exerciseModel->item(row, 2)->text() != "自定义") {
        QMessageBox::warning(this, "错误", "只能删除自定义运动");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  "确定要删除运动 '" + exerciseName + "' 吗？",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 从数据库中删除
        if (dbManager->deleteExerciseItem(exerciseId)) {
            // 从模型中删除
            exerciseModel->removeRow(row);
            QMessageBox::information(this, "成功", "运动已删除");
        } else {
            QMessageBox::critical(this, "错误", "删除失败");
        }
    }
}

