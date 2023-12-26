#include "usercontroller.h"
#include <QDebug>

//静态成员初始化
UserController *UserController::userCtrl_ins=nullptr;

UserController *UserController::getInstance()
{
    if(nullptr==UserController::userCtrl_ins){
        UserController::userCtrl_ins=new UserController;
    }
    return UserController::userCtrl_ins;
}

int UserController::Login(QString account, QString pwd)
{
    int res = -2;
    if(UserModel::getInstance()->selectUser(account,pwd)==0)
    {
        res = UserModel::getInstance()->updateUserStatus(account,1);
    }
    return res;
}

int UserController::userRegist(QString account, QString name, QString pwd)
{
    int res=-2;
    if(UserModel::getInstance()->addUser(account,name,pwd)==0) //注册成功
    {
        qDebug()<<"注册成功";
        res=0;
    }
    else{
        res=-1; //注册失败
    }
    return res;
}

QString UserController::getUserName(QString account)
{
    char **qres=nullptr;    //结果集
    int row=0,col=0;        //结果集的行数与列数
    QString Uname="";
    int res=UserModel::getInstance()->selectUserName(account,qres,row,col);
    if(0==res)  //说明查到了数据
    {
        Uname=qres[col];
    }
    else{
        qDebug()<<"获取用户名失败";
    }
    return Uname;
}

QString UserController::getUserAccount(QString name)
{
    char **qres=nullptr;    //结果集
    int row=0,col=0;        //结果集的行数与列数
    QString account="";
    int res=UserModel::getInstance()->selectUserAccount(name,qres,row,col);
    if(0==res)  //说明查到了数据
    {
        account=qres[col];
    }
    else{
        qDebug()<<"获取用户名失败";
    }
    return account;
}

int UserController::getUserIdByAccount(QString account)
{
    char **qres=nullptr;    //结果集
    int row=0,col=0;        //结果集的行数与列数
    int id=0;
    int res=UserModel::getInstance()->selectIdByAccount(account,qres,row,col);
    if(0==res)  //说明查到了数据
    {
        id=atoi(qres[col]);
    }
    else{
        qDebug()<<"获取用户名失败";
    }
    return id;
}

int UserController::Logout(QString account)
{
    int res=-2;
    res = UserModel::getInstance()->updateUserStatus(account,0);
    return res;//-1:Model的SQL执行失败 0：成功
}

UserController::UserController()
{

}
