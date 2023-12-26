#include "usermodel.h"
#include <QDebug>

//静态成员初始化
UserModel *UserModel::userModel_ins=nullptr;

UserModel *UserModel::getInstance()
{
    if(nullptr==UserModel::userModel_ins)
    {
        UserModel::userModel_ins=new UserModel;
    }
    return UserModel::userModel_ins;
}

int UserModel::selectUser(QString account, QString pwd)
{
    QString loginSelectSQL=QString("SELECT * FROM tbl_user WHERE user_account = '%1' AND user_pwd = '%2';").arg(account,pwd);
    char **qres=nullptr;
    int row=0,col=0;
    //数据库单例
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(loginSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)       //用户名密码存在
        {
            return 0;   //登录成功
        }
        else {
            return 1;   //登录失败
        }
    }
    else {
        return -1;      //SQL执行失败
    }
}

int UserModel::updateUserStatus(QString account, int status)
{
    QString updateSQL=QString("UPDATE tbl_user SET user_status =%1 WHERE user_account = '%2';").arg(status).arg(account);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res = dbInstance->insertDeleteUpdate(updateSQL);
    if(SQLITE_OK==res)
    {
        return 0;
    }
    else {
        return  -1; //更新状态失败
    }
}

int UserModel::addUser(QString account, QString name, QString pwd)
{
    QString accountSelect=QString("SELECT * FROM tbl_user WHERE user_account = '%1';").arg(account);
    char **qres=nullptr;
    int row=0,col=0;
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res = dbInstance->getData(accountSelect,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)   //账号已经存在
        {
            return 1;   //用户名已经存在,注册失败
        }
    }
    else {
        return -1;     //SQL执行失败
    }
    QString userAdd=QString("INSERT INTO tbl_user(user_account,user_name,user_pwd) \
            VALUES('%1','%2','%3');").arg(account,name,pwd);
    res= dbInstance->insertDeleteUpdate(userAdd);
    return 0;
}

int UserModel::selectUserName(QString account,char **&qres,int &row,int &col)
{
    QString userNameSelectSQL=QString("SELECT user_name FROM tbl_user WHERE user_account ='%1';").arg(account);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(userNameSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)   //查到用户名
        {
            return 0;
        }
        else {
            return 1;//未查到数据
        }
    }
    else
    {
        return -1;  //执行失败
    }
}

int UserModel::selectUserAccount(QString name, char **&qres, int &row, int &col)
{
    QString userAccountSelectSQL=QString("SELECT user_account FROM tbl_user WHERE user_name ='%1';").arg(name);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(userAccountSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)   //查到用户名
        {
            return 0;
        }
        else {
            return 1;//未查到数据
        }
    }
    else
    {
        return -1;  //执行失败
    }
}

int UserModel::selectIdByAccount(QString account, char **&qres, int &row, int &col)
{
    QString userAccountSelectSQL=QString("SELECT user_id FROM tbl_user WHERE user_account ='%1';").arg(account);
    Singleton_db *dbInstance=Singleton_db::getInstance();
    int res=dbInstance->getData(userAccountSelectSQL,qres,row,col);
    if(SQLITE_OK==res)
    {
        if(row>0)   //查到用户名
        {
            return 0;
        }
        else {
            return 1;//未查到数据
        }
    }
    else
    {
        return -1;  //执行失败
    }
}

UserModel::UserModel()
{

}
