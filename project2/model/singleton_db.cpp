#include "singleton_db.h"
#include <QDebug>

//初始化单例
Singleton_db* Singleton_db::instance=nullptr;

Singleton_db *Singleton_db::getInstance()
{
    if(nullptr==Singleton_db::instance)
    {
        Singleton_db::instance=new Singleton_db; //静态成员没有this指针
    }
    return  Singleton_db::instance;
}

int Singleton_db::insertDeleteUpdate(QString sql)
{
    char *errmsg=nullptr;
    int res= sqlite3_exec(this->dbconnect,sql.toUtf8(),nullptr,nullptr,&errmsg);
    if(SQLITE_OK==res)
    {
        return 0;
    }
    qDebug()<<sqlite3_errmsg(dbconnect)<<"--insertDeleteUpdate error ";
    qDebug()<<sqlite3_errcode(dbconnect);
    return res;//返回错误码
}

int Singleton_db::getData(QString sql, char **&result, int &row, int &col)
{
    char *errmsg=nullptr;
    int res=sqlite3_get_table(this->dbconnect,sql.toUtf8(),&result,&row,&col,&errmsg);
    if(SQLITE_OK==res)
    {
        return 0; //执行成功
    }
    qDebug()<<sqlite3_errmsg(dbconnect)<<"-- getData error";
    qDebug()<<sqlite3_errcode(dbconnect);
    return res;
}

Singleton_db::Singleton_db()
{
    int res=sqlite3_open("project2.db",&this->dbconnect);
    if(SQLITE_OK==res)
    {
        qDebug()<<"database opensuccess";
    }
    else {
        qDebug()<<sqlite3_errmsg(dbconnect);
        qDebug()<<sqlite3_errcode(dbconnect);
    }
}

Singleton_db::~Singleton_db()
{
    sqlite3_close(this->dbconnect);
}
