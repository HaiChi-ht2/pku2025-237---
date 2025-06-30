#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject{parent}
{
    initDatabase();
}

DatabaseManager::~DatabaseManager()
{
    if(db.isOpen()){
        db.close();
    }
}

bool DatabaseManager::initDatabase()
{
    // 创建SQLite数据库连接
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("notes.db");

    if(!db.open()){
        qDebug() << "无法打开数据库："<< db.lastError().text();
        return false;
    }

/*
    // 删除旧表（如果存在）
    QSqlQuery dropQuery;
    dropQuery.exec("DROP TABLE IF EXISTS notes");
    dropQuery.exec("DROP TABLE IF EXISTS categories");

*/
    //分类表不存在时创建分类表
    QSqlQuery query;

    if (!query.exec("CREATE TABLE IF NOT EXISTS categories ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT UNIQUE NOT NULL)")) {
        qDebug() << "创建分类表失败:" << query.lastError().text();
        return false;
    }
    // 创建笔记表
    if (!query.exec("CREATE TABLE IF NOT EXISTS notes ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "category_id INTEGER NOT NULL,"
                    "title TEXT NOT NULL,"
                    "content TEXT,"
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                    "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                    "FOREIGN KEY (category_id) REFERENCES categories(id) ON DELETE CASCADE,"
                    "UNIQUE (category_id, title))")) {
        qDebug() << "创建笔记表失败:" << query.lastError().text();
        return false;
    }

    //创建食物表
    if(!query.exec("CREATE TABLE IF NOT EXISTS food_items ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT NOT NULL UNIQUE,"
                    "calories REAL NOT NULL,"
                    "unit TEXT NOT NULL," // 单位如'g', 'ml', '个'
                    "is_custom INTEGER DEFAULT 0)")){
        qDebug() << "创建分类表失败:" << query.lastError().text();
        return false;
    }
    //创建锻炼表
    if(!query.exec("CREATE TABLE IF NOT EXISTS exercise_items ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT NOT NULL UNIQUE,"
                    "calories_per_hour REAL NOT NULL,"
                    "is_custom INTEGER DEFAULT 0)")){
        qDebug() << "创建锻炼表失败:" << query.lastError().text();
        return false;
    }
    //创建健康记录表
    if(!query.exec("CREATE TABLE IF NOT EXISTS health_records ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "record_date DATE NOT NULL,"
                    "item_id INTEGER NOT NULL,"
                    "item_type INTEGER NOT NULL," // 0=食物, 1=运动
                    "quantity REAL NOT NULL,"
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)")){
        qDebug() << "创建健康记录表失败:" << query.lastError().text();
        return false;
    }

    if (!query.exec("SELECT COUNT(*) FROM food_items")) {
        qDebug() << "无法检查食物表记录数:" << query.lastError().text();
        return false;
    }
    if (query.next() && query.value(0).toInt() == 0) {
        // 只有当表中没有记录时才插入预定义数据
    //初始化预定义食物数据
        if(!query.exec("INSERT OR IGNORE INTO food_items (name, calories, unit, is_custom) VALUES"
                    "('小麦（谷类及制品）', 338, '100g', 0),"
                    "('小麦粉（代表值，谷类及制品）', 359, '100g', 0),"
                    "('挂面（代表值，谷类及制品）', 353, '100g', 0),"
                    "('面条（生，代表值，谷类及制品）', 301, '100g', 0),"
                    "('通心粉（谷类及制品）', 351, '100g', 0),"
                    "('花卷（谷类及制品）', 214, '100g', 0),"
                    "('馒头（代表值，谷类及制品）', 223, '100g', 0),"
                    "('烙饼（谷类及制品）', 258, '100g', 0),"
                    "('烧饼（加糖，谷类及制品）', 298, '100g', 0),"
                    "('油饼（谷类及制品）', 403, '100g', 0),"
                    "('油条（谷类及制品）', 388, '100g', 0),"
                    "('稻米（代表值，谷类及制品）', 346, '100g', 0),"
                    "('米饭（蒸，谷类及制品）', 116, '100g', 0),"
                    "('米粉（谷类及制品）', 349, '100g', 0),"
                    "('河粉（谷类及制品）', 359, '100g', 0),"
                    "('鲜玉米（谷类及制品）', 112, '100g', 0),"
                    "('小米（谷类及制品）', 361, '100g', 0),"
                    "('小米粥（谷类及制品）', 46, '100g', 0),"
                    "('荞麦（谷类及制品）', 337, '100g', 0),"
                    "('薏米（薏仁米，苡米，谷类及制品）', 361, '100g', 0),"
                    "('莜麦面（谷类及制品）', 391, '100g', 0),"
                    "('燕麦（谷类及制品）', 338, '100g', 0),"
                    "('乌冬面（谷类及制品）', 122, '100g', 0),"
                    "('马铃薯（土豆，洋芋，薯类、淀粉及制品）', 81, '100g', 0),"
                    "('甘薯（白心，薯类、淀粉及制品）', 106, '100g', 0),"
                    "('甘薯（红心，红薯，薯类、淀粉及制品）', 61, '100g', 0),"
                    "('木薯（薯类、淀粉及制品）', 119, '100g', 0),"
                    "('玉米淀粉（薯类、淀粉及制品）', 346, '100g', 0),"
                    "('团粉（芡粉，薯类、淀粉及制品）', 348, '100g', 0),"
                    "('藕粉（薯类、淀粉及制品）', 373, '100g', 0),"
                    "('淀粉（小麦，薯类、淀粉及制品）', 351, '100g', 0),"
                    "('淀粉（大米，薯类、淀粉及制品）', 366, '100g', 0),"
                    "('黄豆（大豆，干豆类及制品）', 390, '100g', 0),"
                    "('黑豆（干，干豆类及制品）', 401, '100g', 0),"
                    "('豆浆粉（干豆类及制品）', 426, '100g', 0),"
                    "('豆腐（内酯，干豆类及制品）', 50, '100g', 0),"
                    "('豆奶（豆乳，干豆类及制品）', 30, '100g', 0),"
                    "('豆汁（生，干豆类及制品）', 10, '100g', 0),"
                    "('豆浆（干豆类及制品）', 34, '100g', 0),"
                    "('豆腐丝（干豆类及制品）', 203, '100g', 0),"
                    "('油豆腐（干豆类及制品）', 245, '100g', 0),"
                    "('腐竹（干豆类及制品）', 461, '100g', 0),"
                    "('豆腐干（干豆类及制品）', 197, '100g', 0),"
                    "('素什锦（干豆类及制品）', 177, '100g', 0),"
                    "('豆腐皮（干豆类及制品）', 447, '100g', 0),"
                    "('绿豆（干，干豆类及制品）', 329, '100g', 0),"
                    "('赤小豆（小豆，红小豆，红豆，干豆类及制品）', 324, '100g', 0),"
                    "('白萝卜（蔬菜及制品）', 16, '100g', 0),"
                    "('红萝卜（蔬菜及制品）', 22, '100g', 0),"
                    "('胡萝卜（蔬菜及制品）', 39, '100g', 0),"
                    "('豆角（蔬菜及制品）', 34, '100g', 0),"
                    "('荷兰豆（蔬菜及制品）', 30, '100g', 0),"
                    "('豌豆（蔬菜及制品）', 111, '100g', 0),"
                    "('四季豆（菜豆，芸豆，蔬菜及制品）', 24, '100g', 0),"
                    "('黄豆芽（蔬菜及制品）', 47, '100g', 0),"
                    "('绿豆芽（蔬菜及制品）', 16, '100g', 0),"
                    "('豌豆苗（蔬菜及制品）', 32, '100g', 0),"
                    "('茄子（代表值，蔬菜及制品）', 23, '100g', 0),"
                    "('番茄（西红柿，蔬菜及制品）', 14, '100g', 0),"
                    "('辣椒（红，尖，蔬菜及制品）', 62, '100g', 0),"
                    "('甜椒（蔬菜及制品）', 22, '100g', 0),"
                    "('秋葵（蔬菜及制品）', 25, '100g', 0),"
                    "('黄瓜（蔬菜及制品）', 16, '100g', 0),"
                    "('苦瓜（蔬菜及制品）', 22, '100g', 0),"
                    "('南瓜（蔬菜及制品）', 23, '100g', 0),"
                    "('冬瓜（蔬菜及制品）', 10, '100g', 0),"
                    "('大蒜（蔬菜及制品）', 128, '100g', 0),"
                    "('蒜黄（蔬菜及制品）', 24, '100g', 0),"
                    "('蒜苗（蔬菜及制品）', 40, '100g', 0),"
                    "('蒜薹（蔬菜及制品）', 66, '100g', 0),"
                    "('大葱（蔬菜及制品）', 28, '100g', 0),"
                    "('小葱（蔬菜及制品）', 27, '100g', 0),"
                    "('洋葱（蔬菜及制品）', 40, '100g', 0),"
                    "('韭黄（蔬菜及制品）', 24, '100g', 0),"
                    "('韭菜（蔬菜及制品）', 25, '100g', 0),"
                    "('大白菜（代表值，蔬菜及制品）', 20, '100g', 0),"
                    "('白菜薹（菜心，蔬菜及制品）', 28, '100g', 0),"
                    "('小油菜（蔬菜及制品）', 12, '100g', 0),"
                    "('小白菜（蔬菜及制品）', 14, '100g', 0),"
                    "('油菜（蔬菜及制品）', 14, '100g', 0),"
                    "('油菜心（蔬菜及制品）', 15, '100g', 0),"
                    "('圆白菜（卷心菜，蔬菜及制品）', 24, '100g', 0),"
                    "('荠菜（雪菜，蔬菜及制品）', 27, '100g', 0),"
                    "('芥蓝（蔬菜及制品）', 24, '100g', 0),"
                    "('菜花（蔬菜及制品）', 20, '100g', 0),"
                    "('菠菜（蔬菜及制品）', 28, '100g', 0),"
                    "('芹菜茎（蔬菜及制品）', 22, '100g', 0),"
                    "('芹菜叶（蔬菜及制品）', 35, '100g', 0),"
                    "('香菜（芫荽，蔬菜及制品）', 33, '100g', 0),"
                    "('苋菜（蔬菜及制品）', 30, '100g', 0),"
                    "('茼蒿（蓬蒿，蔬菜及制品）', 24, '100g', 0),"
                    "('茴香（蔬菜及制品）', 27, '100g', 0),"
                    "('莴笋（莴苣，蔬菜及制品）', 15, '100g', 0),"
                    "('西芹（蔬菜及制品）', 17, '100g', 0),"
                    "('生菜（蔬菜及制品）', 12, '100g', 0),"
                    "('油麦菜（蔬菜及制品）', 12, '100g', 0),"
                    "('竹笋（鲜，蔬菜及制品）', 23, '100g', 0),"
                    "('百合（鲜，蔬菜及制品）', 166, '100g', 0),"
                    "('金针菜（黄花菜，蔬菜及制品）', 214, '100g', 0),"
                    "('莲子（蔬菜及制品）', 89, '100g', 0),"
                    "('茭白（蔬菜及制品）', 26, '100g', 0),"
                    "('荸荠（蔬菜及制品）', 61, '100g', 0),"
                    "('莲藕（蔬菜及制品）', 47, '100g', 0),"
                    "('山药（蔬菜及制品）', 57, '100g', 0),"
                    "('芋头（蔬菜及制品）', 56, '100g', 0),"
                    "('香椿（蔬菜及制品）', 50, '100g', 0),"
                    "('金针菇（菌藻类）', 32, '100g', 0),"
                    "('口蘑（菌藻类）', 277, '100g', 0),"
                    "('蘑菇（鲜蘑，菌藻类）', 24, '100g', 0),"
                    "('木耳（水发，黑木耳，菌藻类）', 27, '100g', 0),"
                    "('香菇（香蕈，菌藻类）', 26, '100g', 0),"
                    "('杏鲍菇（菌藻类）', 35, '100g', 0),"
                    "('海带（菌藻类）', 13, '100g', 0),"
                    "('紫菜（干，菌藻类）', 250, '100g', 0),"
                    "('紫菜（水发，菌藻类）', 36, '100g', 0),"
                    "('裙带菜（水发，菌藻类）', 97, '100g', 0),"
                    "('琼脂（菌藻类）', 311, '100g', 0),"
                    "('苹果（代表值，水果类及制品）', 53, '100g', 0),"
                    "('梨（代表值，水果类及制品）', 51, '100g', 0),"
                    "('红果（山楂，水果类及制品）', 102, '100g', 0),"
                    "('桃（桃子，代表值）', 42, '100g', 0),"
                    "('李子（水果类及制品）', 38, '100g', 0),"
                    "('杏（水果类及制品）', 38, '100g', 0),"
                    "('梅（青梅，水果类及制品）', 34, '100g', 0),"
                    "('枣（鲜，水果类及制品）', 125, '100g', 0),"
                    "('樱桃（水果类及制品）', 46, '100g', 0),"
                    "('葡萄（代表值，水果类及制品）', 45, '100g', 0),"
                    "('葡萄干（水果类及制品）', 344, '100g', 0),"
                    "('石榴（水果类及制品）', 74, '100g', 0),"
                    "('柿（水果类及制品）', 74, '100g', 0),"
                    "('桑葚（水果类及制品）', 60, '100g', 0),"
                    "('沙棘（水果类及制品）', 120, '100g', 0),"
                    "('猕猴桃（水果类及制品）', 61, '100g', 0),"
                    "('草莓（水果类及制品）', 32, '100g', 0),"
                    "('百香果（水果类及制品）', 97, '100g', 0),"
                    "('覆盆子（水果类及制品）', 52, '100g', 0),"
                    "('橙（水果类及制品）', 48, '100g', 0),"
                    "('橘（水果类及制品）', 58, '100g', 0),"
                    "('柚（水果类及制品）', 42, '100g', 0),"
                    "('柠檬（水果类及制品）', 37, '100g', 0),"
                    "('菠萝（水果类及制品）', 44, '100g', 0),"
                    "('菠萝蜜（水果类及制品）', 105, '100g', 0),"
                    "('桂圆（水果类及制品）', 71, '100g', 0),"
                    "('桂圆干（水果类及制品）', 277, '100g', 0),"
                    "('荔枝（水果类及制品）', 71, '100g', 0),"
                    "('芒果（水果类及制品）', 35, '100g', 0),"
                    "('木瓜（水果类及制品）', 29, '100g', 0),"
                    "('人参果（水果类及制品）', 86, '100g', 0),"
                    "('杨梅（水果类及制品）', 30, '100g', 0),"
                    "('杨桃（水果类及制品）', 31, '100g', 0),"
                    "('椰子（水果类及制品）', 241, '100g', 0),"
                    "('火龙果（水果类及制品）', 55, '100g', 0),"
                    "('榴莲（水果类及制品）', 150, '100g', 0),"
                    "('山竹（水果类及制品）', 72, '100g', 0),"
                    "('香蕉（甘蕉，水果类及制品）', 93, '100g', 0),"
                    "('枇杷（水果类及制品）', 41, '100g', 0),"
                    "('哈密瓜（哈蜜瓜，水果类及制品）', 34, '100g', 0),"
                    "('甜瓜（代表值，水果类及制品）', 26, '100g', 0),"
                    "('西瓜（代表值，水果类及制品）', 31, '100g', 0),"
                    "('猪肉（代表值，fat30g，畜肉类及制品）', 331, '100g', 0),"
                    "('猪肉（瘦，畜肉类及制品）', 143, '100g', 0),"
                    "('猪肉（里脊，畜肉类及制品）', 150, '100g', 0),"
                    "('猪蹄（畜肉类及制品）', 260, '100g', 0),"
                    "('猪肝（畜肉类及制品）', 126, '100g', 0),"
                    "('腊肉（培根，畜肉类及制品）', 181, '100g', 0),"
                    "('午餐肉（畜肉类及制品）', 229, '100g', 0),"
                    "('火腿肠（畜肉类及制品）', 212, '100g', 0),"
                    "('香肠（畜肉类及制品）', 508, '100g', 0),"
                    "('牛肉（代表值，fat9g，畜肉类及制品）', 160, '100g', 0),"
                    "('牛蹄筋（泡发，畜肉类及制品）', 25, '100g', 0),"
                    "('牛肚（畜肉类及制品）', 72, '100g', 0),"
                    "('牛肉干（畜肉类及制品）', 550, '100g', 0),"
                    "('羊肉（代表值，fat7g，畜肉类及制品）', 139, '100g', 0),"
                    "('驴肉（畜肉类及制品）', 116, '100g', 0),"
                    "('马肉（畜肉类及制品）', 104, '100g', 0),"
                    "('狗肉（畜肉类及制品）', 116, '100g', 0),"
                    "('兔肉（畜肉类及制品）', 102, '100g', 0),"
                    "('鹿肉（畜肉类及制品）', 92, '100g', 0),"
                    "('鸡肉（禽肉类及制品）', 145, '100g', 0),"
                    "('鸡胸肉（禽肉类及制品）', 118, '100g', 0),"
                    "('鸡腿（禽肉类及制品）', 146, '100g', 0),"
                    "('鸡翅（禽肉类及制品）', 202, '100g', 0),"
                    "('鸡心（禽肉类及制品）', 172, '100g', 0),"
                    "('鸡肫（鸡胗，禽肉类及制品）', 118, '100g', 0),"
                    "('鸡爪（无骨，禽肉类及制品）', 254, '100g', 0),"
                    "('鸭（均值，禽肉类及制品）', 240, '100g', 0),"
                    "('鸭血（白鸭，禽肉类及制品）', 108, '100g', 0),"
                    "('鸭血（公麻鸭，母麻鸭，禽肉类及制品）', 56, '100g', 0),"
                    "('北京烤鸭（禽肉类及制品）', 436, '100g', 0),"
                    "('鹅（禽肉类及制品）', 251, '100g', 0),"
                    "('火鸡腿肉（禽肉类及制品）', 91, '100g', 0),"
                    "('火鸡胸肉（禽肉类及制品）', 103, '100g', 0),"
                    "('鸽（禽肉类及制品）', 201, '100g', 0),"
                    "('乳鸽（禽肉类及制品）', 352, '100g', 0),"
                    "('纯牛奶（代表值，全脂，乳类及制品）', 65, '100g', 0),"
                    "('鲜牛奶（代表值，全脂，乳类及制品）', 63, '100g', 0),"
                    "('羊乳（乳类及制品）', 59, '100g', 0),"
                    "('人乳（乳类及制品）', 65, '100g', 0),"
                    "('全脂奶粉（代表值， 乳类及制品）', 482, '100g', 0),"
                    "('全脂甜奶粉（代表值，乳类及制品）', 484, '100g', 0),"
                    "('低脂奶粉（代表值，乳类及制品）', 425, '100g', 0),"
                    "('酸奶（代表值，全脂，乳类及制品）', 86, '100g', 0),"
                    "('酸奶（脱脂，乳类及制品）', 64, '100g', 0),"
                    "('奶酪（干酪，乳类及制品）', 328, '100g', 0),"
                    "('奶豆腐（脱脂，乳类及制品）', 343, '100g', 0),"
                    "('黄油（乳类及制品）', 888, '100g', 0),"
                    "('奶油（乳类及制品）', 785, '100g', 0),"
                    "('酥油茶（乳类及制品）', 465, '100g', 0),"
                    "('炼乳（甜，罐头，乳类及制品）', 332, '100g', 0),"
                    "('奶片（乳类及制品）', 472, '100g', 0),"
                    "('鸡蛋（代表值，蛋类及制品）', 139, '100g', 0),"
                    "('鸡蛋清（鸡蛋白，蛋类及制品）', 60, '100g', 0),"
                    "('鸡蛋黄（蛋类及制品）', 328, '100g', 0),"
                    "('松花蛋（蛋类及制品）', 178, '100g', 0),"
                    "('鸡蛋（煮，蛋类及制品）', 143, '100g', 0),"
                    "('鸭蛋（蛋类及制品）', 180, '100g', 0),"
                    "('鸭蛋白（鸭蛋清，蛋类及制品）', 47, '100g', 0),"
                    "('鸭蛋黄（蛋类及制品）', 378, '100g', 0),"
                    "('鹅蛋（蛋类及制品）', 196, '100g', 0),"
                    "('鹅蛋白（鹅蛋清，蛋类及制品）', 48, '100g', 0),"
                    "('鹅蛋黄（蛋类及制品）', 324, '100g', 0),"
                    "('鹌鹑蛋（蛋类及制品）', 160, '100g', 0),"
                    "('草鱼（鱼虾蟹贝类）', 113, '100g', 0),"
                    "('黄鳝（鳝鱼，鱼虾蟹贝类）', 89, '100g', 0),"
                    "('鲤鱼（鱼虾蟹贝类）', 109, '100g', 0),"
                    "('罗非鱼（鱼虾蟹贝类）', 98, '100g', 0),"
                    "('泥鳅（鱼虾蟹贝类）', 96, '100g', 0),"
                    "('青鱼（鱼虾蟹贝类）', 118, '100g', 0),"
                    "('乌鳢（黑鱼，乌鱼，鱼虾蟹贝类）', 85, '100g', 0),"
                    "('鲢鱼（白鲢，鱼虾蟹贝类）', 104, '100g', 0),"
                    "('鲫鱼（鱼虾蟹贝类）', 108, '100g', 0),"
                    "('鳙鱼（胖头鱼，花鲢，鱼虾蟹贝类）', 100, '100g', 0),"
                    "('鳜鱼（鱼虾蟹贝类）', 117, '100g', 0),"
                    "('鳟鱼（鱼虾蟹贝类）', 99, '100g', 0),"
                    "('鲥鱼（鱼虾蟹贝类）', 189, '100g', 0),"
                    "('鲟鱼（鱼虾蟹贝类）', 100, '100g', 0),"
                    "('带鱼（鱼虾蟹贝类）', 127, '100g', 0),"
                    "('沙丁鱼（鱼虾蟹贝类）', 89, '100g', 0),"
                    "('鲅鱼（鱼虾蟹贝类）', 121, '100g', 0),"
                    "('鲈鱼（鱼虾蟹贝类）', 105, '100g', 0),"
                    "('鲑鱼（三文鱼，大马哈鱼，鱼虾蟹贝类）', 139, '100g', 0),"
                    "('鲑鱼子酱（鱼籽酱，三文鱼子酱，鱼虾蟹贝类）', 252, '100g', 0),"
                    "('鳕鱼（鱼虾蟹贝类）', 88, '100g', 0),"
                    "('黄鱼（黄花鱼，鱼虾蟹贝类）', 114, '100g', 0),"
                    "('鲳鱼（鱼虾蟹贝类）', 149, '100g', 0),"
                    "('金枪鱼（鱼虾蟹贝类）', 102, '100g', 0),"
                    "('鱼排（鱼虾蟹贝类）', 160, '100g', 0),"
                    "('鱼丸（鱼虾蟹贝类）', 107, '100g', 0),"
                    "('鱼子酱（鱼籽酱，鱼虾蟹贝类）', 201, '100g', 0),"
                    "('白米虾（水虾米，鱼虾蟹贝类）', 81, '100g', 0),"
                    "('对虾（大虾，鱼虾蟹贝类）', 93, '100g', 0),"
                    "('海虾（鱼虾蟹贝类）', 79, '100g', 0),"
                    "('河虾（鱼虾蟹贝类）', 87, '100g', 0),"
                    "('基围虾（鱼虾蟹贝类）', 101, '100g', 0),"
                    "('龙虾（鱼虾蟹贝类）', 90, '100g', 0),"
                    "('明虾（鱼虾蟹贝类）', 85, '100g', 0),"
                    "('青虾（鱼虾蟹贝类）', 100, '100g', 0),"
                    "('虾米（海米，虾仁，鱼虾蟹贝类）', 198, '100g', 0),"
                    "('虾酱（鱼虾蟹贝类）', 112, '100g', 0),"
                    "('虾皮（鱼虾蟹贝类）', 153, '100g', 0),"
                    "('虾仁（鱼虾蟹贝类）', 199, '100g', 0),"
                    "('海蟹（鱼虾蟹贝类）', 95, '100g', 0),"
                    "('河蟹（鱼虾蟹贝类）', 103, '100g', 0),"
                    "('梭子蟹（鱼虾蟹贝类）', 95, '100g', 0),"
                    "('蟹肉（鱼虾蟹贝类）', 62, '100g', 0),"
                    "('大闸蟹（母，鱼虾蟹贝类）', 152, '100g', 0),"
                    "('蟹膏（大闸蟹，蒸，鱼虾蟹贝类）', 167, '100g', 0),"
                    "('蟹黄（大闸蟹，蒸，鱼虾蟹贝类）', 255, '100g', 0),"
                    "('鲍鱼（鱼虾蟹贝类）', 84, '100g', 0),"
                    "('蛏子（鱼虾蟹贝类）', 40, '100g', 0),"
                    "('河蚌（鱼虾蟹贝类）', 54, '100g', 0),"
                    "('牡蛎（鱼虾蟹贝类）', 73, '100g', 0),"
                    "('河蚬（鱼虾蟹贝类）', 47, '100g', 0),"
                    "('生蚝（鱼虾蟹贝类）', 57, '100g', 0),"
                    "('扇贝（鲜，鱼虾蟹贝类）', 60, '100g', 0),"
                    "('扇贝（干，干贝，鱼虾蟹贝类）', 264, '100g', 0),"
                    "('鲜贝（鱼虾蟹贝类）', 77, '100g', 0),"
                    "('蛤蜊（均值，鱼虾蟹贝类）', 62, '100g', 0),"
                    "('螺（均值，鱼虾蟹贝类）', 100, '100g', 0),"
                    "('螺蛳（鱼虾蟹贝类）', 59, '100g', 0),"
                    "('田螺（鱼虾蟹贝类）', 60, '100g', 0),"
                    "('海蚌（鲜，鱼虾蟹贝类）', 51, '100g', 0),"
                    "('海参（鱼虾蟹贝类）', 78, '100g', 0),"
                    "('海参（干，鱼虾蟹贝类）', 262, '100g', 0),"
                    "('海参（水浸，鱼虾蟹贝类）', 25, '100g', 0),"
                    "('海蜇皮（鱼虾蟹贝类）', 33, '100g', 0),"
                    "('墨鱼（鲜，曼氏无针乌贼，鱼虾蟹贝类）', 83, '100g', 0),"
                    "('鱿鱼（鲜，中国枪乌贼，鱼虾蟹贝类）', 84, '100g', 0),"
                    "('乌鱼蛋（鱼虾蟹贝类）', 66, '100g', 0),"
                    "('章鱼（八爪鱼，鱼虾蟹贝类）', 52, '100g', 0),"
                    "('甲鱼蛋（鱼虾蟹贝类）', 128, '100g', 0),"
                    "('乌龟（龟板，鱼虾蟹贝类）', 466, '100g', 0),"
                    "('茶汤（小吃、甜饼）', 93, '100g', 0),"
                    "('炒肝（小吃、甜饼）', 96, '100g', 0),"
                    "('春卷（小吃、甜饼）', 465, '100g', 0),"
                    "('豆腐脑（带卤，小吃、甜饼）', 48, '100g', 0),"
                    "('灌肠（小吃、甜饼）', 134, '100g', 0),"
                    "('煎饼（小吃、甜饼）', 354, '100g', 0),"
                    "('焦圈（小吃、甜饼）', 534, '100g', 0),"
                    "('京八件（小吃、甜饼）', 441, '100g', 0),"
                    "('凉粉（小吃、甜饼）', 38, '100g', 0),"
                    "('凉粉（带调料，小吃、甜饼）', 51, '100g', 0),"
                    "('凉面（小吃、甜饼）', 167, '100g', 0),"
                    "('驴打滚（小吃、甜饼）', 198, '100g', 0),"
                    "('年糕（小吃、甜饼）', 156, '100g', 0),"
                    "('热干面（小吃、甜饼）', 153, '100g', 0),"
                    "('炸糕（小吃、甜饼）', 282, '100g', 0),"
                    "('黑芝麻汤圆（小吃、甜饼）', 311, '100g', 0),"
                    "('醪糟（小吃、甜饼）', 100, '100g', 0),"
                    "('过桥米线（小吃、甜饼）', 92, '100g', 0),"
                    "('蛋糕（小吃、甜饼）', 348, '100g', 0),"
                    "('蛋清蛋糕（小吃、甜饼）', 320, '100g', 0),"
                    "('奶油蛋糕（小吃、甜饼）', 379, '100g', 0),"
                    "('巧克力蛋糕（小吃、甜饼）', 437, '100g', 0),"
                    "('水果蛋糕（小吃、甜饼）', 347, '100g', 0),"
                    "('月饼（豆沙，小吃、甜饼）', 411, '100g', 0),"
                    "('蛋黄酥（小吃、甜饼）', 388, '100g', 0),"
                    "('江米条（小吃、甜饼）', 440, '100g', 0),"
                    "('绿豆糕（小吃、甜饼）', 351, '100g', 0),"
                    "('麻花（小吃、甜饼）', 527, '100g', 0),"
                    "('米花糖（小吃、甜饼）', 385, '100g', 0),"
                    "('桃酥（小吃、甜饼）', 483, '100g', 0),"
                    "('沙琪玛蛋酥（小吃、甜饼）', 506, '100g', 0),"
                    "('麦片（速食食品）', 368, '100g', 0),"
                    "('燕麦片（速食食品）', 377, '100g', 0),"
                    "('早餐奶（速食食品）', 68, '100g', 0),"
                    "('黑芝麻糊粉（速食食品）', 408, '100g', 0),"
                    "('方便面（速食食品）', 473, '100g', 0),"
                    "('韭菜盒子（韭菜合子，速食食品）', 211, '100g', 0),"
                    "('什锦炒饭（速食食品）', 188, '100g', 0),"
                    "('面包（速食食品）', 313, '100g', 0),"
                    "('面包屑（速食食品）', 355, '100g', 0),"
                    "('饼干（速食食品）', 435, '100g', 0),"
                    "('钙奶饼干（速食食品）', 446, '100g', 0),"
                    "('苏打饼干（速食食品）', 408, '100g', 0),"
                    "('饼干（三明治，速食食品）', 515, '100g', 0),"
                    "('饼干（夹心，速食食品）', 449, '100g', 0),"
                    "('马铃薯片（油炸土豆片，速食食品）', 615, '100g', 0),"
                    "('雪米饼（速食食品）', 463, '100g', 0),"
                    "('洋葱圈（速食食品）', 476, '100g', 0),"
                    "('虾片（速食食品）', 523, '100g', 0),"
                    "('海苔（速食食品）', 177, '100g', 0),"
                    "('锅巴（速食食品）', 528, '100g', 0),"
                    "('乐芙球（速食食品）', 537, '100g', 0),"
                    "('啤酒（含酒精饮料）', 32, '100g', 0),"
                    "('葡萄酒（含酒精饮料）', 72, '100g', 0),"
                    "('黑加仑酒（含酒精饮料）', 51, '100g', 0),"
                    "('雪莉酒（雪利酒，含酒精饮料）', 116, '100g', 0),"
                    "('黄酒（含酒精饮料）', 66, '100g', 0),"
                    "('伏特加（含酒精饮料）', 234, '100g', 0),"
                    "('威士忌（含酒精饮料）', 252, '100g', 0),"
                    "('蜜酒（含酒精饮料）', 84, '100g', 0),"
                    "('香雪酒（含酒精饮料）', 37, '100g', 0),"
                    "('白砂糖（白糖，糖、蜜饯类）', 400, '100g', 0),"
                    "('绵白糖（糖、蜜饯类）', 396, '100g', 0),"
                    "('冰糖（糖、蜜饯类）', 397, '100g', 0),"
                    "('红糖（糖、蜜饯类）', 389, '100g', 0),"
                    "('麦芽糖（糖、蜜饯类）', 331, '100g', 0),"
                    "('蜂蜜（糖、蜜饯类）', 321, '100g', 0),"
                    "('棉花糖（糖、蜜饯类）', 321, '100g', 0),"
                    "('花生牛轧糖（糖、蜜饯类）', 432, '100g', 0),"
                    "('奶糖（糖、蜜饯类）', 407, '100g', 0),"
                    "('巧克力（糖、蜜饯类）', 589, '100g', 0),"
                    "('酱油（调味品类）', 63, '100g', 0),"
                    "('老抽（调味品类）', 129, '100g', 0),"
                    "('生抽（调味品类）', 20, '100g', 0),"
                    "('醋（调味品类）', 31, '100g', 0),"
                    "('白醋（调味品类）', 6, '100g', 0),"
                    "('陈醋（调味品类）', 114, '100g', 0),"
                    "('香醋（调味品类）', 68, '100g', 0),"
                    "('豆瓣酱（调味品类）', 181, '100g', 0),"
                    "('花生酱（调味品类）', 600, '100g', 0),"
                    "('黄酱（大酱，调味品类）', 138, '100g', 0),"
                    "('辣椒酱（辣椒糊，调味品类）', 36, '100g', 0),"
                    "('蒜蓉辣酱（调味品类）', 96, '100g', 0),"
                    "('芝麻酱（调味品类）', 630, '100g', 0),"
                    "('郫县辣酱（调味品类）', 106, '100g', 0),"
                    "('沙拉酱（调味品类）', 725, '100g', 0),"
                    "('千岛沙拉酱（千岛酱，调味品类）', 475, '100g', 0),"
                    "('番茄酱（调味品类）', 85, '100g', 0),"
                    "('番茄沙司（调味品类）', 112, '100g', 0),"
                    "('榨菜（调味品类）', 33, '100g', 0),"
                    "('胡椒粉（调味品类）', 361, '100g', 0),"
                    "('芥末（调味品类）', 490, '100g', 0),"
                    "('辣椒粉（调味品类）', 290, '100g', 0),"
                    "('五香粉（调味品类）', 359, '100g', 0),"
                    "('咖喱粉（调味品类）', 415, '100g', 0),"
                    "('味精（调味品类）', 268, '100g', 0),"
                    "('鸡精（调味品类）', 195, '100g', 0),"
                    "('蛋黄酱（调味品类）', 372, '100g', 0)"
                   )){
        qDebug() << "食物表预载失败:" << query.lastError().text();
        return false;
        }
    }

    if (!query.exec("SELECT COUNT(*) FROM exercise_items")) {
        qDebug() << "无法检查运动表记录数:" << query.lastError().text();
        return false;
    }
    if (query.next() && query.value(0).toInt() == 0) {
    //初始化锻炼表
        if(!query.exec("INSERT OR IGNORE INTO exercise_items (name, calories_per_hour, is_custom) VALUES "
                    "('慢走，每小时5km', 150, 0),"
                    "('徒步', 438, 0),"
                    "('行走', 314, 0),"
                    "('水中有氧运动', 402, 0),"
                    "('游泳，轻度或中等强度', 423, 0),"
                    "('健身操', 420, 0),"
                    "('划船机', 440, 0),"
                    "('跳绳', 700, 0),"
                    "('低强度有氧', 365, 0),"
                    "('跑步', 600, 0),"
                    "('游泳', 500, 0),"
                    "('休闲骑行，小于16km/h', 292, 0),"
                    "('瑜伽', 240, 0),"
                    "('篮球', 480, 0)"
                    )){
        qDebug() << "锻炼表初始化失败:" << query.lastError().text();
        return false;
        }
    }
    return true;
}

void DatabaseManager::testDatabase()
{
    qDebug() << "===== 开始数据库测试 =====";
    QString testCategory = "测试分类_" + QString::number(QDateTime::currentSecsSinceEpoch());
    if (addCategory(testCategory))
    {
        qDebug() << "添加分类测试通过";

        int catId = getCategoryId(testCategory);
        if(catId != -1){
            qDebug()<<"获取分类Id测试通过";

            int noteId = addNote(catId, "测试笔记", "这是测试内容");
            if(noteId != -1){
                qDebug() << "添加笔记测试通过";

                QStringList notes = getNotesByCategory(catId);
                if (!notes.isEmpty()) {
                    qDebug() << "获取笔记列表测试通过";

                    QString content = getNoteContent(noteId);
                    if (!content.isEmpty()) {
                        qDebug() << "获取笔记内容测试通过";
                    }
                    else {
                        qDebug() << "获取笔记内容测试失败";
                    }
                }
                else {
                    qDebug() << "获取笔记列表测试失败";
                }
                deleteNote(noteId);
            }
            else {
                qDebug() << "添加笔记测试失败";
            }
            deleteCategory(testCategory);
        }
        else {
            qDebug() << "获取分类ID测试失败";
        }
    }
    else {
        qDebug() << "添加分类测试失败";
    }
    qDebug() << "===== 数据库测试完成 =====";
}


bool DatabaseManager::addCategory(const QString &categoryName)
{
    if(!isDatabaseOpen()) return false;
    QSqlQuery query;
    query.prepare("INSERT INTO categories (name) VALUES (?)");
    query.addBindValue(categoryName);

    if (!query.exec()) {
        qDebug() << "添加分类失败:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::deleteCategory(const QString &categoryName)
{
    if (!isDatabaseOpen()) return false;
    QSqlQuery query;
    query.prepare("DELETE FROM categories WHERE name = ?");
    query.addBindValue(categoryName);

    if (!query.exec()) {
        qDebug() << "删除分类失败:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::updateCategory(const QString &oldName, const QString &newName)
{
    if (!isDatabaseOpen()) return false;

    // 开始事务
    db.transaction();

    //更新分类名
    QSqlQuery query;
    query.prepare("UPDATE categories SET name = :newName WHERE name = :oldName");
    query.bindValue(":newName", newName);
    query.bindValue(":oldName", oldName);

    if(!query.exec()){
        qDebug() << "更新分类名失败:" << query.lastError().text();
        qDebug() << "执行的SQL:" << query.lastQuery();
        db.rollback();
        return false;
    }
    /*
    // 更新关联的笔记
    query.prepare("UPDATE notes SET category = :newName WHERE category = :oldName");
    query.bindValue(":newName", newName);
    query.bindValue(":oldName", oldName);

    if (!query.exec()) {
        qDebug() << "更新关联笔记失败:" << query.lastError().text();
        db.rollback();
        return false;
    }*/

    // 提交事务
    return db.commit();
}

QStringList DatabaseManager::getALLCategories() const
{
    QStringList categories;
    if(!isDatabaseOpen()) return categories;

    QSqlQuery query("SELECT name FROM categories");

    while (query.next()) {
        categories.append(query.value(0).toString());
    }

    return categories;
}
//查找分类是否存在
bool DatabaseManager::categoryExists(const QString &categoryName) const
{
    if (!isDatabaseOpen()) return false;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM categories WHERE name = :name");
    query.bindValue(":name", categoryName);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
//增加笔记
int DatabaseManager::addNote(int categoryId, const QString &title, const QString &content)
{
    if (!isDatabaseOpen()) return -1;

    qDebug() << "添加笔记 - 分类ID:" << categoryId << "标题:" << title;

    QSqlQuery query;
    // 使用 ? 位置占位符
    query.prepare("INSERT INTO notes (category_id, title, content) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(categoryId);
    query.addBindValue(title);
    query.addBindValue(content);

    if (!query.exec()) {
        qDebug() << "添加笔记失败:" << query.lastError().text();
        qDebug() << "执行的SQL:" << query.lastQuery();
        return -1;
    }

    int noteId = query.lastInsertId().toInt();
    qDebug() << "添加笔记成功，ID:" << noteId;
    return noteId;
}
//更新笔记
bool DatabaseManager::updateNote(int noteId, const QString &newTitle, const QString &content)
{
    if (!isDatabaseOpen()) return false;

    db.transaction();

    QSqlQuery query;
    // 使用 ? 位置占位符
    query.prepare("UPDATE notes SET title = ?, content = ?, updated_at = CURRENT_TIMESTAMP "
                  "WHERE id = ?");
    query.addBindValue(newTitle);
    query.addBindValue(content);
    query.addBindValue(noteId);

    if (!query.exec()) {
        qDebug() << "更新笔记失败:" << query.lastError().text();
        qDebug() << "执行的SQL:" << query.lastQuery();
        db.rollback();
        return false;
    }
    return db.commit();
}
//删除笔记
bool DatabaseManager::deleteNote(int noteId)
{
    if (!isDatabaseOpen()) return false;
    db.transaction();

    QSqlQuery query;
    query.prepare("DELETE FROM notes WHERE id = :id");
    query.bindValue(":id", noteId);

    if (!query.exec()) {
        qDebug() << "删除笔记失败:" << query.lastError().text();
        qDebug() << "执行的SQL:" << query.lastQuery();
        db.rollback();
        return false;
    }

    return db.commit();
}
//删除所有分类
bool DatabaseManager::deleteAllCategories()
{
    if(!isDatabaseOpen()) return false;
    //开始事务
    db.transaction();

    QSqlQuery query;
    query.prepare("DELETE FROM categories WHERE name != :defaultName");
    query.bindValue(":defaultName", "默认");
    if(!query.exec()){
        qDebug() << "删除分类失败：" << query.lastError().text();
        db.rollback();
        return false;
    }
    //提交事务
    return db.commit();
}


//通过分类寻找笔记
QStringList DatabaseManager::getNotesByCategory(int categoryId) const
{
    QStringList notes;

    if (!isDatabaseOpen()) {
        qDebug() << "数据库未打开，无法获取笔记列表";
        return notes;
    }

    QSqlQuery query;
    // 使用 ? 位置占位符
    query.prepare("SELECT id, title FROM notes WHERE category_id = ? ORDER BY updated_at DESC");
    query.addBindValue(categoryId);

    if (query.exec()) {
        while (query.next()) {
            // 返回格式: "笔记ID;笔记标题"
            notes.append(query.value(0).toString() + ";" + query.value(1).toString());
        }
    }
    else{
        qDebug() << "获取笔记列表失败:" << query.lastError().text();
        qDebug() << "执行的SQL:" << query.lastQuery();
    }

    return notes;
}
//获取笔记内容
QString DatabaseManager::getNoteContent(int noteId) const
{
    if (!isDatabaseOpen()) return QString();

    QSqlQuery query;
    // 使用 ? 位置占位符
    query.prepare("SELECT content FROM notes WHERE id = ?");
    query.addBindValue(noteId);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    else {
        qDebug() << "获取笔记内容失败:" << query.lastError().text();
        qDebug() << "执行的SQL:" << query.lastQuery();
    }

    return QString();
}
//获取笔记id
int DatabaseManager::getNoteId(int categoryId, const QString &title) const
{
    if (!isDatabaseOpen()) return -1;

    QSqlQuery query;
    query.prepare("SELECT id FROM notes WHERE category_id = :categoryId AND title = :title");
    query.bindValue(":categoryId", categoryId);
    query.bindValue(":title", title);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    return -1; // 未找到返回-1
}
//查找分类的id
int DatabaseManager::getCategoryId(const QString &categoryName) const
{
    if(!isDatabaseOpen()) return -1;

    QSqlQuery query;
    query.prepare("SELECT id FROM categories WHERE name = ?");
    query.addBindValue(categoryName);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    else {
        qDebug() << "获取分类id失败:" << query.lastError().text();
        qDebug() << "执行的SQL:" << query.lastQuery();
    }
    return -1; // 未找到
}

//数据库是否打开
bool DatabaseManager::isDatabaseOpen() const
{
    return db.isOpen();
}

//添加自定义食物
bool DatabaseManager::addCustomFood(const QString &name, double calories, const QString &unit)
{
    QSqlQuery query;
    query.prepare("INSERT INTO food_items (name, calories, unit, is_custom) "
                  "VALUES (?, ?, ?, 1)");
    query.addBindValue(name);
    query.addBindValue(calories);
    query.addBindValue(unit);
    return query.exec();
}

//添加自定义运动
bool DatabaseManager::addCustomExercise(const QString &name, double caloriesPerHour)
{
    QSqlQuery query;
    query.prepare("INSERT INTO exercise_items (name, calories_per_hour, is_custom) "
                  "VALUES (?, ?, 1)");
    query.addBindValue(name);
    query.addBindValue(caloriesPerHour);
    return query.exec();
}

//记录饮食
bool DatabaseManager::logFoodConsumption(int foodId, double quantity, const QDate &date)
{
    QSqlQuery query;
    query.prepare("INSERT INTO health_records (record_date, item_id, item_type, quantity) "
                  "VALUES (?, ?, 0, ?)");
    query.addBindValue(date.toString(Qt::ISODate));
    query.addBindValue(foodId);
    query.addBindValue(quantity);
    return query.exec();

}

//记录运动条目
bool DatabaseManager::logExercise(int exerciseId, double durationHours, const QDate &date)
{
    QSqlQuery query;
    query.prepare("INSERT INTO health_records (record_date, item_id, item_type, quantity) "
                  "VALUES (?, ?, 1, ?)");
    query.addBindValue(date.toString(Qt::ISODate));
    query.addBindValue(exerciseId);
    query.addBindValue(durationHours);
    return query.exec();

}
//获取所有食物项
QList<FoodItem> DatabaseManager::getAllFoodItems(bool includeCustom)
{
    QList<FoodItem> items;
    if (!isDatabaseOpen()) return items;

    QSqlQuery query;
    QString sql = includeCustom
                      ? "SELECT id, name, calories, unit, is_custom FROM food_items"
                      : "SELECT id, name, calories, unit, is_custom FROM food_items WHERE is_custom = 0";

    if (query.exec(sql)) {
        while (query.next()) {
            FoodItem item;
            item.id = query.value(0).toInt();
            item.name = query.value(1).toString();
            item.calories = query.value(2).toDouble();
            item.unit = query.value(3).toString();
            item.isCustom = query.value(4).toBool();
            items.append(item);
        }
    } else {
        qDebug() << "获取食物列表失败:" << query.lastError().text();
    }
    return items;
}

//获取所有运动项
QList<ExerciseItem> DatabaseManager::getAllExerciseItems(bool includeCustom)
{
    QList<ExerciseItem> items;
    if (!isDatabaseOpen()) return items;

    QSqlQuery query;
    QString sql = includeCustom
                      ? "SELECT id, name, calories_per_hour, is_custom FROM exercise_items"
                      : "SELECT id, name, calories_per_hour, is_custom FROM exercise_items WHERE is_custom = 0";
    if (query.exec(sql)) {
        while (query.next()) {
            ExerciseItem item;
            item.id = query.value(0).toInt();
            item.name = query.value(1).toString();
            item.caloriesPerHour = query.value(2).toDouble();
            item.isCustom = query.value(3).toBool();
            items.append(item);
        }
    } else {
        qDebug() << "获取运动列表失败:" << query.lastError().text();
    }
    return items;

}

//获取日热量
DailyCalories DatabaseManager::getDailyCalories(const QDate &date)
{
    DailyCalories data;
    data.date = date;
    data.intake = 0.0;
    data.expenditure = 0.0;

    if (!isDatabaseOpen()) return data;

    // 计算摄入热量
    QSqlQuery foodQuery;
    foodQuery.prepare(
        "SELECT SUM(f.calories * h.quantity) "
        "FROM health_records h "
        "JOIN food_items f ON h.item_id = f.id "
        "WHERE h.item_type = 0 AND h.record_date = ?"
        );
    foodQuery.addBindValue(date.toString(Qt::ISODate));
    if (foodQuery.exec() && foodQuery.next()) {
        data.intake = foodQuery.value(0).toDouble();
    }

    // 计算消耗热量
    QSqlQuery exerciseQuery;
    exerciseQuery.prepare(
        "SELECT SUM(e.calories_per_hour * h.quantity) "
        "FROM health_records h "
        "JOIN exercise_items e ON h.item_id = e.id "
        "WHERE h.item_type = 1 AND h.record_date = ?"
        );
    exerciseQuery.addBindValue(date.toString(Qt::ISODate));
    if (exerciseQuery.exec() && exerciseQuery.next()) {
        data.expenditure = exerciseQuery.value(0).toDouble();
    }

    return data;

}
//删除食物
bool DatabaseManager::deleteFoodItem(int foodId)
{
    if (!isDatabaseOpen()) return false;

    QSqlQuery query;
    query.prepare("DELETE FROM food_items WHERE id = ? AND is_custom = 1");
    query.addBindValue(foodId);

    if (!query.exec()) {
        qDebug() << "删除食物失败:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}
//删除运动
bool DatabaseManager::deleteExerciseItem(int exerciseId)
{
    if (!isDatabaseOpen()) return false;

    QSqlQuery query;
    query.prepare("DELETE FROM exercise_items WHERE id = ? AND is_custom = 1");
    query.addBindValue(exerciseId);

    if (!query.exec()) {
        qDebug() << "删除运动失败:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

//清理重复数据
void DatabaseManager::cleanDuplicateHealthData()
{
    if (!isDatabaseOpen()) return;

    // 清理重复食物数据
    QSqlQuery query;
    query.exec("DELETE FROM food_items WHERE id NOT IN ("
               "SELECT MIN(id) FROM food_items GROUP BY name)");

    // 清理重复运动数据
    query.exec("DELETE FROM exercise_items WHERE id NOT IN ("
               "SELECT MIN(id) FROM exercise_items GROUP BY name)");

    // 清理健康记录中的无效数据
    query.exec("DELETE FROM health_records WHERE item_id NOT IN "
               "(SELECT id FROM food_items) AND item_type = 0");
    query.exec("DELETE FROM health_records WHERE item_id NOT IN "
               "(SELECT id FROM exercise_items) AND item_type = 1");
}


