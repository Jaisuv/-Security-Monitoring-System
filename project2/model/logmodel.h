#ifndef LOGMODEL_H
#define LOGMODEL_H
#include "singleton_db.h"
#include <QString>
#include <QDebug>

class LogModel
{
public:
    static LogModel *getInstance();
/************************************************************
* 函数名称：
* 函数功能：添加操作日志
* 参   数:
* 返 回 值:
**************************************************************/
    int addLog(int UserId,QString UserName,QString datetime,QString operatin);
/************************************************************
* 函数名称：
* 函数功能：获取日志
* 参   数:
* 返 回 值:
**************************************************************/
    int getLatestLog(int offset,char **&qres,int &row,int &col);
private:
    LogModel();
    static LogModel* logModel_ins;
};

#endif // LOGMODEL_H
