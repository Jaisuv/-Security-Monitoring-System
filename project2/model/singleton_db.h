#ifndef SINGLETON_DB_H
#define SINGLETON_DB_H
#include <QString>
#include "sqlite3.h"

class Singleton_db
{
public:
    static Singleton_db* getInstance();
    //数据增撒改
    int insertDeleteUpdate(QString sql);
    //查询并获取数据
    int getData(QString sql, char**& result,int &row,int &col);
private:
    Singleton_db();
    ~Singleton_db();
    static Singleton_db* instance;
    sqlite3* dbconnect;
};

#endif // SINGLETON_DB_H
