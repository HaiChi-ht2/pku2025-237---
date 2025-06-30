#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QList>
#include <QDate>
#include <QPair>

//食物结构体
struct FoodItem {
    int id;
    QString name;
    double calories;
    QString unit;
    bool isCustom;
};
//运动
struct ExerciseItem {
    int id;
    QString name;
    double caloriesPerHour;
    bool isCustom;
};
//每日消耗
struct DailyCalories {
    QDate date;
    double intake;
    double expenditure;
};

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool initDatabase();
    void testDatabase();

    //分类管理
    bool addCategory(const QString &categoryName);
    bool deleteCategory(const QString &categoryName);
    bool updateCategory(const QString &oldName, const QString &newName);
    QStringList getALLCategories() const;
    bool categoryExists(const QString &categoryName) const;
    bool deleteAllCategories();
    int getCategoryId(const QString &categoryName) const;

    //笔记管理
    int addNote(int categoryId, const QString &title, const QString &content);
    bool updateNote(int noteId, const QString &newTitle, const QString &content);
    bool deleteNote(int noteId);
    QStringList getNotesByCategory(int categoryId) const;
    QString getNoteContent(int noteId) const;
    int getNoteId(int categoryId, const QString &title) const; // 新增,根据分类ID和标题获取笔记ID

    //运动健康管理
    bool addCustomFood(const QString &name, double calories, const QString &unit);
    bool addCustomExercise(const QString &name, double caloriesPerHour);
    bool logFoodConsumption(int foodId, double quantity, const QDate &date);
    bool logExercise(int exerciseId, double durationHours, const QDate &date);
    QList<FoodItem> getAllFoodItems(bool includeCustom = true);
    QList<ExerciseItem> getAllExerciseItems(bool includeCustom = true);
    DailyCalories getDailyCalories(const QDate &date);

    bool deleteFoodItem(int foodId);
    bool deleteExerciseItem(int exerciseId);

    //检测数据库是否打开
    bool isDatabaseOpen() const;

    void cleanDuplicateHealthData();

private:
    QSqlDatabase db;

signals:
};

#endif // DATABASEMANAGER_H
