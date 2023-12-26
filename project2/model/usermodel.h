#ifndef USERMODEL_H
#define USERMODEL_H
#include <QString>
#include "singleton_db.h"

class UserModel
{
public:
    static UserModel *getInstance();
    int selectUser(QString account,QString pwd);
    int updateUserStatus(QString account,int status);
    int addUser(QString account,QString name,QString pwd);
    int selectUserName(QString account,char **&qres,int &row,int &col);
    int selectUserAccount(QString name,char **&qres,int &row,int &col);
    int selectIdByAccount(QString account,char **&qres,int &row,int &col);
private:
    UserModel();    //构造私有化
    static UserModel *userModel_ins;
};

#endif // USERMODEL_H
