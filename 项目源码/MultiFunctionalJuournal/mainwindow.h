#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include<QTimer>
#include <QStandardItemModel>
#include "databasemanager.h"
#include <QDateTimeEdit>
#include <QAction>
#include <QSettings>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionNew_File_triggered();


    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actioncut_triggered();

    void on_actioncopy_triggered();

    void on_actionpaste_triggered();

    void on_actionundo_triggered();

    void on_actionredo_triggered();

    void on_actionAbout_triggered();

    void on_actionopen_triggered();

    void on_pushButton_clicked();

    void on_actionHome_triggered();



    void on_addBtn_clicked();

    void on_categoryList_itemDoubleClicked(QListWidgetItem *item);

    void on_deleteBtn_clicked();

    void on_deleteAllClassBtn_clicked();

    //void saveCategories();

    void on_editClassBtn_clicked();

    void on_noteList_itemDoubleClicked(QListWidgetItem *item);

    void on_newNoteBtn_clicked();

    void on_editNoteBtn_clicked();

    void on_deleteNoteBtn_clicked();

    void on_backToCategoryBtn_clicked();

    void on_fileSaveBtn_clicked();

    void on_quitEditBtn_clicked();

    void on_backToHomePageBtn_clicked();

    void on_clearButton_clicked();

    void on_clearButtonText_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_new_clicked();

    void on_pushButton_saveAccount_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_edit_clicked();

    void updateBudgetDisplay();

    void calculateUsedAmount();

    void on_btnSaveTodo_clicked();

    void on_btnDeleteTodo_clicked();

    void Todo_sort();

private:
    Ui::MainWindow *ui;
    QString currentCategory;
    int currentCategoryId;
    int currentNoteId;
    QTimer searchTimer;
    QTimer searchTimer_text;
    QStandardItemModel *account_list_model;
    double currentBudget = 0.0;
    double usedAmount = 0.0;
    bool warningShowed=false;

    DatabaseManager *dbManager;

    QStandardItemModel *foodModel;
    QStandardItemModel *exerciseModel;

    //初始化分类表
    void initCategoryList();

    //从数据库加载
    void loadCategoriesFromDatabase();

    //刷新分类显示
    void refreshCategoryList();

    //加载分类下笔记
    void loadNotesForCurrentCategory();

    void filterList(const QString &filtertext);
    void performFilter(const QString &filtertext);
    void filterList_text(const QString &filtertext);
    void performFilter_text(const QString &filtertext);

    //初始化运动健康UI
    void initHealthPage();

    //刷新食物运动列表
    void refreshFoodList();
    void refreshExerciseList();



private:
    QStandardItemModel *todoModel ;

private slots:
    void on_pushButton_2_clicked();
    void on_btnAdd_clicked();

private slots:
    void checkDeadlines(); // 新增定时检查函数
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_addFoodBtn_clicked();

    void on_logFoodBtn_clicked();

    void on_addExerciseBtn_clicked();

    void on_logExerciseBtn_clicked();

    void updateCalorieDisplay();

    void onLogDateChanged(const QDate &date);

    void on_pushButton_4_clicked();

    void on_back_to_menuBtn_clicked();

    void on_deleteFoodBtn_clicked();

    void on_deleteExerciseBtn_clicked();

private:
    QTimer *alertTimer;    // 定时器指针

};
#endif // MAINWINDOW_H
