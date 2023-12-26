#include "logcontroller.h"

LogController* LogController::logController_ins=nullptr;

LogController *LogController::getInstance()
{
    if(nullptr==LogController::logController_ins)
    {
        LogController::logController_ins=new LogController;
    }
    return LogController::logController_ins;
}

int LogController::addLog(int UserId, QString UserName, QString datetime, QString operatin)
{
    int res=-2;
    if(LogModel::getInstance()->addLog(UserId,UserName,datetime,operatin)==0)
    {
        res=0;
    }
    return res;
}

QList<MyLog *> LogController::getlogList(int start)
{
    QList<MyLog *> logList;
    char **qres=nullptr;
    int row=0,col=0;
    int res=LogModel::getInstance()->getLatestLog(start,qres,row,col);
    if(res==0)
    {
        if(row>0)
        {
            for (int i=1;i<=row;i++) {
               logList.push_back(new MyLog(atoi(qres[i*col]),atoi(qres[i*col+1]),qres[i*col+2],qres[i*col+3],qres[i*col+4]));
            }
        }
        else {
            qDebug()<<"Get data error!";
        }
    }
    else {
        qDebug()<<"Get Video data failed.";
    }
    return logList;
}

LogController::LogController()
{

}
