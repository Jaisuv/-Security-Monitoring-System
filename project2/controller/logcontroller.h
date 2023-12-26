#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H
#include <QString>
#include "model/logmodel.h"
#include "MyClass/mylog.h"
#include <QList>

class LogController
{
public:
    static LogController* getInstance();
    int addLog(int UserId,QString UserName,QString datetime,QString operatin);
    QList<MyLog *> getlogList(int start);
private:
    LogController();
    static LogController* logController_ins;
};

#endif // LOGCONTROLLER_H
