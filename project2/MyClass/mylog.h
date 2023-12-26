#ifndef MYLOG_H
#define MYLOG_H
#include <QString>

class MyLog
{
public:
    MyLog(int log_id,int user_id,QString user_name,QString datetime,QString operation);
    int getLog_id() const;
    void setLog_id(int value);

    int getUser_id() const;
    void setUser_id(int value);

    QString getUser_name() const;
    void setUser_name(const QString &value);

    QString getDatetime() const;
    void setDatetime(const QString &value);

    QString getOperation() const;
    void setOperation(const QString &value);

private:
    int log_id;
    int user_id;
    QString user_name;
    QString datetime;
    QString operation;
};

#endif // MYLOG_H
