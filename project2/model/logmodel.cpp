#include "logmodel.h"

LogModel* LogModel::logModel_ins=nullptr;

LogModel *LogModel::getInstance()
{
    if(LogModel::logModel_ins==nullptr)
    {
        LogModel::logModel_ins=new LogModel;
    }
    return LogModel::logModel_ins;
}

int LogModel::addLog(int UserId, QString UserName, QString datetime, QString operatin)
{
    QString insertLogSQL=QString("INSERT INTO tbl_log(user_id,user_name,datetime,operation)\
                                 VALUES(%1,'%2','%3','%4');").arg(UserId).arg(UserName,datetime,operatin);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->insertDeleteUpdate(insertLogSQL);
    if(SQLITE_OK==res)
    {
        return 0;
    }
    else {
        return -1;
    }
}

int LogModel::getLatestLog(int offset, char **&qres, int &row, int &col)
{
    QString initLogSelectSQL=QString("SELECT * FROM tbl_log ORDER BY datetime DESC LIMIT 20 OFFSET %1;").arg(offset);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(initLogSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)
        {
            return 0; //查找到数据
        }
        else {
            return 1;   //无数据
        }
    }
    else {
        return -1;  //执行SQL失败
    }
}

LogModel::LogModel()
{

}
