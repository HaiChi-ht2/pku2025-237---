/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_File;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionHome;
    QAction *actioncut;
    QAction *actioncopy;
    QAction *actionpaste;
    QAction *actionundo;
    QAction *actionredo;
    QAction *actionAbout;
    QAction *actionopen;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;
    QWidget *page_chooseClass;
    QLabel *label_2;
    QLabel *label_3;
    QListWidget *categoryList;
    QLineEdit *categoryEdit;
    QPushButton *addBtn;
    QPushButton *deleteBtn;
    QPushButton *deleteAllClassBtn;
    QPushButton *editClassBtn;
    QPushButton *backToHomePageBtn;
    QLabel *label_4;
    QLineEdit *searchEdit;
    QLabel *statusLabel;
    QPushButton *clearButton;
    QWidget *page_classDetail;
    QListWidget *noteList;
    QPushButton *newNoteBtn;
    QPushButton *editNoteBtn;
    QPushButton *deleteNoteBtn;
    QPushButton *backToCategoryBtn;
    QLabel *label_5;
    QLineEdit *searchEditText;
    QLabel *statusLabelText;
    QPushButton *clearButtonText;
    QWidget *page_txt;
    QTextEdit *textEdit;
    QLineEdit *titleEdit;
    QPushButton *fileSaveBtn;
    QPushButton *quitEditBtn;
    QWidget *page_accounting;
    QLabel *label_budget_display;
    QPushButton *pushButton_new;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_edit;
    QPushButton *pushButton_back;
    QPushButton *pushButton_clear;
    QTableView *tableView_account;
    QPushButton *pushButton_saveAccount;
    QWidget *page_todo;
    QTableView *tableView;
    QPushButton *btnAdd;
    QPushButton *btnSaveTodo;
    QPushButton *btnDeleteTodo;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *page_health_and_exercise;
    QPushButton *back_to_menuBtn;
    QDateEdit *logDateEdit;
    QLabel *intakeLabel;
    QLabel *expenditureLabel;
    QLabel *balanceLabel;
    QLineEdit *foodNameEdit;
    QLineEdit *foodUnitEdit;
    QDoubleSpinBox *foodCaloriesSpin;
    QDoubleSpinBox *foodQuantitiesSpin;
    QLineEdit *exerciseNameEdit;
    QDoubleSpinBox *exerciseCaloriesSpin;
    QDoubleSpinBox *exerciseDurationSpin;
    QTableView *tableView_food;
    QTableView *tableView_exercise;
    QPushButton *addFoodBtn;
    QPushButton *logFoodBtn;
    QPushButton *addExerciseBtn;
    QPushButton *logExerciseBtn;
    QPushButton *deleteFoodBtn;
    QPushButton *deleteExerciseBtn;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QMenuBar *menubar;
    QMenu *file;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionNew_File = new QAction(MainWindow);
        actionNew_File->setObjectName("actionNew_File");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
        actionNew_File->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        actionSave->setIcon(icon1);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName("actionSave_as");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs));
        actionSave_as->setIcon(icon2);
        actionHome = new QAction(MainWindow);
        actionHome->setObjectName("actionHome");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));
        actionHome->setIcon(icon3);
        actioncut = new QAction(MainWindow);
        actioncut->setObjectName("actioncut");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::EditCut));
        actioncut->setIcon(icon4);
        actioncopy = new QAction(MainWindow);
        actioncopy->setObjectName("actioncopy");
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::EditCopy));
        actioncopy->setIcon(icon5);
        actionpaste = new QAction(MainWindow);
        actionpaste->setObjectName("actionpaste");
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::EditPaste));
        actionpaste->setIcon(icon6);
        actionundo = new QAction(MainWindow);
        actionundo->setObjectName("actionundo");
        QIcon icon7(QIcon::fromTheme(QIcon::ThemeIcon::EditUndo));
        actionundo->setIcon(icon7);
        actionredo = new QAction(MainWindow);
        actionredo->setObjectName("actionredo");
        QIcon icon8(QIcon::fromTheme(QIcon::ThemeIcon::EditRedo));
        actionredo->setIcon(icon8);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        QIcon icon9(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout));
        actionAbout->setIcon(icon9);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName("actionopen");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(280, 170, 121, 41));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(280, 230, 121, 41));
        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(280, 290, 121, 41));
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(280, 350, 121, 41));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(250, 110, 181, 31));
        stackedWidget->addWidget(page);
        page_chooseClass = new QWidget();
        page_chooseClass->setObjectName("page_chooseClass");
        label_2 = new QLabel(page_chooseClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 91, 51));
        label_3 = new QLabel(page_chooseClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 310, 81, 41));
        categoryList = new QListWidget(page_chooseClass);
        categoryList->setObjectName("categoryList");
        categoryList->setGeometry(QRect(80, 100, 311, 192));
        categoryList->setStyleSheet(QString::fromUtf8("background-color:rgb(85, 85, 127);"));
        categoryEdit = new QLineEdit(page_chooseClass);
        categoryEdit->setObjectName("categoryEdit");
        categoryEdit->setGeometry(QRect(80, 360, 311, 31));
        addBtn = new QPushButton(page_chooseClass);
        addBtn->setObjectName("addBtn");
        addBtn->setGeometry(QRect(450, 360, 80, 31));
        deleteBtn = new QPushButton(page_chooseClass);
        deleteBtn->setObjectName("deleteBtn");
        deleteBtn->setGeometry(QRect(629, 360, 81, 31));
        deleteAllClassBtn = new QPushButton(page_chooseClass);
        deleteAllClassBtn->setObjectName("deleteAllClassBtn");
        deleteAllClassBtn->setGeometry(QRect(450, 260, 80, 31));
        editClassBtn = new QPushButton(page_chooseClass);
        editClassBtn->setObjectName("editClassBtn");
        editClassBtn->setGeometry(QRect(630, 260, 80, 31));
        backToHomePageBtn = new QPushButton(page_chooseClass);
        backToHomePageBtn->setObjectName("backToHomePageBtn");
        backToHomePageBtn->setGeometry(QRect(0, 10, 80, 24));
        label_4 = new QLabel(page_chooseClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(450, 60, 61, 16));
        searchEdit = new QLineEdit(page_chooseClass);
        searchEdit->setObjectName("searchEdit");
        searchEdit->setGeometry(QRect(450, 90, 251, 31));
        statusLabel = new QLabel(page_chooseClass);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(450, 140, 261, 31));
        clearButton = new QPushButton(page_chooseClass);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(610, 47, 80, 31));
        stackedWidget->addWidget(page_chooseClass);
        page_classDetail = new QWidget();
        page_classDetail->setObjectName("page_classDetail");
        noteList = new QListWidget(page_classDetail);
        noteList->setObjectName("noteList");
        noteList->setGeometry(QRect(60, 130, 641, 261));
        noteList->setStyleSheet(QString::fromUtf8("background-color:rgb(85, 85, 127)"));
        newNoteBtn = new QPushButton(page_classDetail);
        newNoteBtn->setObjectName("newNoteBtn");
        newNoteBtn->setGeometry(QRect(60, 430, 91, 31));
        editNoteBtn = new QPushButton(page_classDetail);
        editNoteBtn->setObjectName("editNoteBtn");
        editNoteBtn->setGeometry(QRect(240, 430, 91, 31));
        deleteNoteBtn = new QPushButton(page_classDetail);
        deleteNoteBtn->setObjectName("deleteNoteBtn");
        deleteNoteBtn->setGeometry(QRect(450, 430, 91, 31));
        backToCategoryBtn = new QPushButton(page_classDetail);
        backToCategoryBtn->setObjectName("backToCategoryBtn");
        backToCategoryBtn->setGeometry(QRect(0, 10, 80, 24));
        label_5 = new QLabel(page_classDetail);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(130, 10, 121, 16));
        searchEditText = new QLineEdit(page_classDetail);
        searchEditText->setObjectName("searchEditText");
        searchEditText->setGeometry(QRect(130, 40, 391, 31));
        statusLabelText = new QLabel(page_classDetail);
        statusLabelText->setObjectName("statusLabelText");
        statusLabelText->setGeometry(QRect(130, 90, 391, 16));
        clearButtonText = new QPushButton(page_classDetail);
        clearButtonText->setObjectName("clearButtonText");
        clearButtonText->setGeometry(QRect(560, 40, 91, 31));
        stackedWidget->addWidget(page_classDetail);
        page_txt = new QWidget();
        page_txt->setObjectName("page_txt");
        textEdit = new QTextEdit(page_txt);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 30, 788, 531));
        textEdit->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"font: 9pt \"\345\256\213\344\275\223\";\n"
"font: 9pt \"\351\273\221\344\275\223\";"));
        titleEdit = new QLineEdit(page_txt);
        titleEdit->setObjectName("titleEdit");
        titleEdit->setGeometry(QRect(0, 0, 381, 23));
        fileSaveBtn = new QPushButton(page_txt);
        fileSaveBtn->setObjectName("fileSaveBtn");
        fileSaveBtn->setGeometry(QRect(379, 0, 201, 24));
        quitEditBtn = new QPushButton(page_txt);
        quitEditBtn->setObjectName("quitEditBtn");
        quitEditBtn->setGeometry(QRect(579, 0, 201, 24));
        stackedWidget->addWidget(page_txt);
        page_accounting = new QWidget();
        page_accounting->setObjectName("page_accounting");
        label_budget_display = new QLabel(page_accounting);
        label_budget_display->setObjectName("label_budget_display");
        label_budget_display->setGeometry(QRect(290, 10, 141, 31));
        pushButton_new = new QPushButton(page_accounting);
        pushButton_new->setObjectName("pushButton_new");
        pushButton_new->setGeometry(QRect(50, 380, 91, 41));
        pushButton_delete = new QPushButton(page_accounting);
        pushButton_delete->setObjectName("pushButton_delete");
        pushButton_delete->setGeometry(QRect(220, 380, 91, 41));
        pushButton_edit = new QPushButton(page_accounting);
        pushButton_edit->setObjectName("pushButton_edit");
        pushButton_edit->setGeometry(QRect(600, 10, 81, 31));
        pushButton_back = new QPushButton(page_accounting);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(60, 10, 71, 31));
        pushButton_clear = new QPushButton(page_accounting);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setGeometry(QRect(410, 380, 91, 41));
        tableView_account = new QTableView(page_accounting);
        tableView_account->setObjectName("tableView_account");
        tableView_account->setGeometry(QRect(90, 70, 551, 291));
        tableView_account->setStyleSheet(QString::fromUtf8("color: rgb(144, 249, 255);\n"
"border-color: rgb(52, 34, 255);"));
        pushButton_saveAccount = new QPushButton(page_accounting);
        pushButton_saveAccount->setObjectName("pushButton_saveAccount");
        pushButton_saveAccount->setGeometry(QRect(580, 380, 101, 41));
        stackedWidget->addWidget(page_accounting);
        page_todo = new QWidget();
        page_todo->setObjectName("page_todo");
        tableView = new QTableView(page_todo);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(50, 90, 611, 231));
        btnAdd = new QPushButton(page_todo);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(180, 30, 111, 31));
        btnSaveTodo = new QPushButton(page_todo);
        btnSaveTodo->setObjectName("btnSaveTodo");
        btnSaveTodo->setGeometry(QRect(510, 350, 91, 31));
        btnDeleteTodo = new QPushButton(page_todo);
        btnDeleteTodo->setObjectName("btnDeleteTodo");
        btnDeleteTodo->setGeometry(QRect(530, 30, 101, 31));
        pushButton_5 = new QPushButton(page_todo);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 10, 81, 31));
        pushButton_6 = new QPushButton(page_todo);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(140, 350, 91, 31));
        stackedWidget->addWidget(page_todo);
        page_health_and_exercise = new QWidget();
        page_health_and_exercise->setObjectName("page_health_and_exercise");
        back_to_menuBtn = new QPushButton(page_health_and_exercise);
        back_to_menuBtn->setObjectName("back_to_menuBtn");
        back_to_menuBtn->setGeometry(QRect(10, 10, 80, 31));
        logDateEdit = new QDateEdit(page_health_and_exercise);
        logDateEdit->setObjectName("logDateEdit");
        logDateEdit->setGeometry(QRect(620, 40, 110, 24));
        intakeLabel = new QLabel(page_health_and_exercise);
        intakeLabel->setObjectName("intakeLabel");
        intakeLabel->setGeometry(QRect(100, 40, 101, 31));
        expenditureLabel = new QLabel(page_health_and_exercise);
        expenditureLabel->setObjectName("expenditureLabel");
        expenditureLabel->setGeometry(QRect(250, 40, 121, 31));
        balanceLabel = new QLabel(page_health_and_exercise);
        balanceLabel->setObjectName("balanceLabel");
        balanceLabel->setGeometry(QRect(400, 40, 171, 31));
        foodNameEdit = new QLineEdit(page_health_and_exercise);
        foodNameEdit->setObjectName("foodNameEdit");
        foodNameEdit->setGeometry(QRect(40, 400, 111, 23));
        foodUnitEdit = new QLineEdit(page_health_and_exercise);
        foodUnitEdit->setObjectName("foodUnitEdit");
        foodUnitEdit->setGeometry(QRect(40, 430, 111, 23));
        foodCaloriesSpin = new QDoubleSpinBox(page_health_and_exercise);
        foodCaloriesSpin->setObjectName("foodCaloriesSpin");
        foodCaloriesSpin->setGeometry(QRect(40, 500, 111, 24));
        foodCaloriesSpin->setMaximum(999.990000000000009);
        foodCaloriesSpin->setSingleStep(10.000000000000000);
        foodQuantitiesSpin = new QDoubleSpinBox(page_health_and_exercise);
        foodQuantitiesSpin->setObjectName("foodQuantitiesSpin");
        foodQuantitiesSpin->setGeometry(QRect(40, 470, 111, 21));
        exerciseNameEdit = new QLineEdit(page_health_and_exercise);
        exerciseNameEdit->setObjectName("exerciseNameEdit");
        exerciseNameEdit->setGeometry(QRect(420, 400, 111, 23));
        exerciseCaloriesSpin = new QDoubleSpinBox(page_health_and_exercise);
        exerciseCaloriesSpin->setObjectName("exerciseCaloriesSpin");
        exerciseCaloriesSpin->setGeometry(QRect(420, 500, 111, 24));
        exerciseCaloriesSpin->setMaximum(1999.990000000000009);
        exerciseCaloriesSpin->setSingleStep(10.000000000000000);
        exerciseDurationSpin = new QDoubleSpinBox(page_health_and_exercise);
        exerciseDurationSpin->setObjectName("exerciseDurationSpin");
        exerciseDurationSpin->setGeometry(QRect(420, 450, 111, 24));
        tableView_food = new QTableView(page_health_and_exercise);
        tableView_food->setObjectName("tableView_food");
        tableView_food->setGeometry(QRect(30, 80, 341, 301));
        tableView_exercise = new QTableView(page_health_and_exercise);
        tableView_exercise->setObjectName("tableView_exercise");
        tableView_exercise->setGeometry(QRect(390, 80, 351, 301));
        addFoodBtn = new QPushButton(page_health_and_exercise);
        addFoodBtn->setObjectName("addFoodBtn");
        addFoodBtn->setGeometry(QRect(230, 400, 111, 24));
        logFoodBtn = new QPushButton(page_health_and_exercise);
        logFoodBtn->setObjectName("logFoodBtn");
        logFoodBtn->setGeometry(QRect(230, 450, 111, 24));
        addExerciseBtn = new QPushButton(page_health_and_exercise);
        addExerciseBtn->setObjectName("addExerciseBtn");
        addExerciseBtn->setGeometry(QRect(620, 400, 111, 24));
        logExerciseBtn = new QPushButton(page_health_and_exercise);
        logExerciseBtn->setObjectName("logExerciseBtn");
        logExerciseBtn->setGeometry(QRect(620, 450, 111, 24));
        deleteFoodBtn = new QPushButton(page_health_and_exercise);
        deleteFoodBtn->setObjectName("deleteFoodBtn");
        deleteFoodBtn->setGeometry(QRect(230, 500, 111, 24));
        deleteExerciseBtn = new QPushButton(page_health_and_exercise);
        deleteExerciseBtn->setObjectName("deleteExerciseBtn");
        deleteExerciseBtn->setGeometry(QRect(620, 500, 111, 24));
        label_6 = new QLabel(page_health_and_exercise);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(160, 470, 71, 16));
        label_7 = new QLabel(page_health_and_exercise);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(160, 500, 61, 16));
        label_8 = new QLabel(page_health_and_exercise);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(540, 450, 54, 16));
        label_9 = new QLabel(page_health_and_exercise);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(540, 500, 54, 16));
        label_10 = new QLabel(page_health_and_exercise);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(160, 400, 54, 16));
        label_11 = new QLabel(page_health_and_exercise);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(160, 430, 54, 16));
        label_12 = new QLabel(page_health_and_exercise);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(540, 400, 54, 16));
        stackedWidget->addWidget(page_health_and_exercise);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        file = new QMenu(menubar);
        file->setObjectName("file");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(file->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuHelp->menuAction());
        file->addAction(actionNew_File);
        file->addAction(actionopen);
        file->addAction(actionSave);
        file->addAction(actionSave_as);
        file->addAction(actionHome);
        menuEdit->addAction(actioncut);
        menuEdit->addAction(actioncopy);
        menuEdit->addAction(actionpaste);
        menuEdit->addAction(actionundo);
        menuEdit->addAction(actionredo);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_File->setText(QCoreApplication::translate("MainWindow", "New File", nullptr));
#if QT_CONFIG(tooltip)
        actionNew_File->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew_File->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_as->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_as->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionHome->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
#if QT_CONFIG(tooltip)
        actionHome->setToolTip(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionHome->setShortcut(QCoreApplication::translate("MainWindow", "Home", nullptr));
#endif // QT_CONFIG(shortcut)
        actioncut->setText(QCoreApplication::translate("MainWindow", "cut", nullptr));
#if QT_CONFIG(tooltip)
        actioncut->setToolTip(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actioncut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actioncopy->setText(QCoreApplication::translate("MainWindow", "copy", nullptr));
#if QT_CONFIG(tooltip)
        actioncopy->setToolTip(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actioncopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionpaste->setText(QCoreApplication::translate("MainWindow", "paste", nullptr));
#if QT_CONFIG(tooltip)
        actionpaste->setToolTip(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionpaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionundo->setText(QCoreApplication::translate("MainWindow", "undo", nullptr));
#if QT_CONFIG(tooltip)
        actionundo->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionundo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionredo->setText(QCoreApplication::translate("MainWindow", "redo", nullptr));
#if QT_CONFIG(tooltip)
        actionredo->setToolTip(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionredo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
#endif // QT_CONFIG(tooltip)
        actionopen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(tooltip)
        actionopen->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionopen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\256\260\344\272\213\346\234\254", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\276\205\345\212\236", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\350\256\260\350\264\246", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\350\277\220\345\212\250\344\270\216\345\201\245\345\272\267", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:11pt; color:#173aff;\">\345\244\232\345\212\237\350\203\275\346\227\245\345\277\227\357\274\210Demo\357\274\211</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\351\200\211\346\213\251\345\210\206\347\261\273</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\345\210\233\345\273\272\345\210\206\347\261\273</p></body></html>", nullptr));
        addBtn->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        deleteBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\211\200\351\200\211\345\210\206\347\261\273", nullptr));
        deleteAllClassBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\205\250\351\203\250\345\210\206\347\261\273", nullptr));
        editClassBtn->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        backToHomePageBtn->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\345\210\206\347\261\273", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\345\205\263\351\224\256\345\255\227\345\274\200\345\247\213\346\220\234\347\264\242", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244", nullptr));
        newNoteBtn->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        editNoteBtn->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        deleteNoteBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        backToCategoryBtn->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\346\226\207\344\273\266\345\220\215/\345\206\205\345\256\271", nullptr));
        statusLabelText->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\345\205\263\351\224\256\345\255\227\345\274\200\345\247\213\346\220\234\347\264\242", nullptr));
        clearButtonText->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244", nullptr));
        fileSaveBtn->setText(QCoreApplication::translate("MainWindow", "Save and Quit", nullptr));
        quitEditBtn->setText(QCoreApplication::translate("MainWindow", "Quit the Editor", nullptr));
        label_budget_display->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt;\">\346\202\250\347\232\204\351\242\204\350\256\276\351\242\235\345\272\246\357\274\232</span></p></body></html>", nullptr));
        pushButton_new->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\226\260\346\235\241\347\233\256", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\255\244\346\235\241\347\233\256", nullptr));
        pushButton_edit->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271", nullptr));
        pushButton_back->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\346\211\200\346\234\211\346\235\241\347\233\256", nullptr));
        pushButton_saveAccount->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        btnSaveTodo->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        btnDeleteTodo->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\346\216\250\350\215\220\345\256\214\346\210\220\351\241\272\345\272\217", nullptr));
        back_to_menuBtn->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        intakeLabel->setText(QCoreApplication::translate("MainWindow", "\346\221\204\345\205\245 kcal", nullptr));
        expenditureLabel->setText(QCoreApplication::translate("MainWindow", "\346\266\210\350\200\227 kcal", nullptr));
        balanceLabel->setText(QCoreApplication::translate("MainWindow", "\346\200\273\346\224\266\346\224\257 kcal", nullptr));
#if QT_CONFIG(tooltip)
        foodNameEdit->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\350\257\267\350\276\223\345\205\245\351\243\237\347\211\251\345\220\215\347\247\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        foodNameEdit->setText(QString());
#if QT_CONFIG(tooltip)
        foodUnitEdit->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\350\257\267\350\276\223\345\205\245\350\264\250\351\207\217\345\215\225\344\275\215</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        foodUnitEdit->setText(QString());
#if QT_CONFIG(tooltip)
        exerciseNameEdit->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\350\257\267\350\276\223\345\205\245\350\277\220\345\212\250\345\220\215\347\247\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        exerciseNameEdit->setText(QString());
        addFoodBtn->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\351\243\237\347\211\251", nullptr));
        logFoodBtn->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\351\245\256\351\243\237\350\256\260\345\275\225", nullptr));
        addExerciseBtn->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\277\220\345\212\250\351\241\271\347\233\256", nullptr));
        logExerciseBtn->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\277\220\345\212\250\350\256\260\345\275\225", nullptr));
        deleteFoodBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\243\237\347\211\251", nullptr));
        deleteExerciseBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\277\220\345\212\250\351\241\271\347\233\256", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\350\264\250\351\207\217(\345\215\225\344\275\215)", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "kcal/\345\215\225\344\275\215", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\215\225\344\275\215\346\227\266\351\225\277", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "kcal/\345\215\225\344\275\215", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\351\243\237\347\211\251\345\220\215\347\247\260", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\345\215\225\344\275\215\350\264\250\351\207\217", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\350\277\220\345\212\250\351\241\271\347\233\256", nullptr));
        file->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
