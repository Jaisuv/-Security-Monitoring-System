#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H
#include <QString>
#include "model/usermodel.h"

class UserController
{
public:
    static UserController *getInstance();
    int Login(QString account,QString pwd);
    int userRegist(QString account,QString name,QString pwd);
    QString getUserName(QString account);   //根据账号找名字
    QString getUserAccount(QString name);   //根据名字找账号
    int getUserIdByAccount(QString account);
    int Logout(QString account);
private:
    UserController();
    static UserController *userCtrl_ins;
};

#endif // USERCONTROLLER_H
