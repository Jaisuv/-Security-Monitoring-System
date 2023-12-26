#include "mylog.h"


MyLog::MyLog(int log_id, int user_id, QString user_name, QString datetime, QString operation)
{
    this->log_id=log_id;
    this->user_id=user_id;
    this->user_name=user_name;
    this->datetime=datetime;
    this->operation=operation;
}

int MyLog::getLog_id() const
{
    return log_id;
}

void MyLog::setLog_id(int value)
{
    log_id = value;
}

int MyLog::getUser_id() const
{
    return user_id;
}

void MyLog::setUser_id(int value)
{
    user_id = value;
}

QString MyLog::getUser_name() const
{
    return user_name;
}

void MyLog::setUser_name(const QString &value)
{
    user_name = value;
}

QString MyLog::getDatetime() const
{
    return datetime;
}

void MyLog::setDatetime(const QString &value)
{
    datetime = value;
}

QString MyLog::getOperation() const
{
    return operation;
}

void MyLog::setOperation(const QString &value)
{
    operation = value;
}




