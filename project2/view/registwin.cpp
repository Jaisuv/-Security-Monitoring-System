#include "registwin.h"
#include <QIcon>
#include <QFile>
#include <QDebug>
#include <QMessageBox> //信息提示窗
#include <QRegExpValidator>
#include "sqlite3.h"
#include "tools/getmd5.h"
#include "controller/logcontroller.h"
#include <QDateTime>

RegistWin::RegistWin(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("注册");
    this->setWindowIcon(QIcon(":/images/bootloadwinicon.png"));
    this->setGeometry(300,400,600,450);
    this->setObjectName("RegistWin");

    this->icon1=QIcon(":/images/visible.png");
    this->icon2=QIcon(":/images/unvisible.png");
    this->pwdVisible=false;
    this->cfpwdVisible=false;

    this->initCtrl();
    this->loadQSS();
    this->initConnect();
}

void RegistWin::initCtrl()
{
    this->title=new QLabel("用户注册",this);
    this->title->setObjectName("title");
    this->title->move(235,30);

    this->accountLab=new QLabel("  账 号 ",this);
    this->accountLab->move(130,100);

    this->accountEdt=new QLineEdit(this);
    this->accountEdt->move(220,90);
    QRegExp regExp1("[0-9a-zA-Z]{6,}");//创建正则表达式模式 最少要6位数字和英文大小写字母
    QRegExpValidator *validator1=new QRegExpValidator(regExp1,this);//创建验证器并设置正则表达式模式
    this->accountEdt->setValidator(validator1);//将上述验证器应用于用户名输入框
    this->accountEdt->setMaxLength(10);

    this->nameLab=new QLabel("  昵 称 ",this);
    this->nameLab->move(130,170);

    this->nameEdt=new QLineEdit(this);
    this->nameEdt->move(220,160);
    this->nameEdt->setMaxLength(10);
    this->nameEdt->setValidator(validator1);

    this->pwdLab=new QLabel("  密 码 ",this);
    this->pwdLab->move(130,240);

    this->pwdEdt=new QLineEdit(this);
    this->pwdEdt->move(220,230);
    this->pwdEdt->setEchoMode(QLineEdit::Password);
    this->pwdEdt->setMaxLength(10);
    this->pwdEdt->setValidator(validator1);

    this->cfpwdLab=new QLabel("确认密码",this);
    this->cfpwdLab->move(130,310);

    this->cfpwdEdt=new QLineEdit(this);
    this->cfpwdEdt->move(220,300);
    this->cfpwdEdt->setEchoMode(QLineEdit::Password);
    this->cfpwdEdt->setMaxLength(10);
    this->cfpwdEdt->setValidator(validator1);

    this->okBtn=new QPushButton("确定",this);
    this->okBtn->move(160,370);

    this->cancelBtn=new QPushButton("取消",this);
    this->cancelBtn->move(350,370);

    this->eye1=new QPushButton(this);
    this->eye1->setFixedSize(36,36);
    this->eye1->move(390,230);
    this->eye1->setIcon(this->icon2);
    this->eye1->setStyleSheet("background-color: transparent;");
    this->eye1->setIconSize(QSize(30,30));

    this->eye2=new QPushButton(this);
    this->eye2->setFixedSize(36,36);
    this->eye2->move(390,300);
    this->eye2->setIcon(this->icon2);
    this->eye2->setStyleSheet("background-color: transparent;");
    this->eye2->setIconSize(QSize(30,30));
}

void RegistWin::loadQSS()
{
    QFile registqss(":/qss/regist.qss");
    if(registqss.open(QFile::ReadOnly))
    {
        qDebug()<<"Open Successfully!";//qDebug()函数：输出信息
        QString style=QLatin1String(registqss.readAll());
        this->setStyleSheet(style);//为窗口设置样式
        registqss.close();//打开文件后，要关闭文件
    }
    else
    {
        qDebug()<<"Open Failed!";
    }
}

void RegistWin::initConnect()
{
    connect(this->eye1,SIGNAL(clicked()),this,SLOT(pwd_EchoMode_Sw()));
    connect(this->eye2,SIGNAL(clicked()),this,SLOT(cfpwd_EchoMode_Sw()));
    connect(this->okBtn,SIGNAL(clicked()),this,SLOT(Regist()));
    connect(this->cancelBtn,SIGNAL(clicked()),this,SLOT(clickCancelBtn()));
}

void RegistWin::initUI()
{
    this->accountEdt->clear();
    this->nameEdt->clear();
    this->pwdEdt->clear();
    this->pwdEdt->setEchoMode(QLineEdit::Password);
    this->cfpwdEdt->clear();
    this->cfpwdEdt->setEchoMode(QLineEdit::Password);
    this->eye1->setIcon(this->icon2);
    this->eye2->setIcon(this->icon2);
}

void RegistWin::pwd_EchoMode_Sw()
{
    this->pwdVisible=!this->pwdVisible;
    if(this->pwdVisible)
    {
        this->eye1->setIcon(this->icon1);
        this->pwdEdt->setEchoMode(QLineEdit::Normal);
    }
    else {
        this->eye1->setIcon(this->icon2);
        this->pwdEdt->setEchoMode(QLineEdit::Password);
    }
}

void RegistWin::cfpwd_EchoMode_Sw()
{
    this->cfpwdVisible=!this->cfpwdVisible;
    if(this->cfpwdVisible)
    {
        this->eye2->setIcon(this->icon1);
        this->cfpwdEdt->setEchoMode(QLineEdit::Normal);
    }
    else {
        this->eye2->setIcon(this->icon2);
        this->cfpwdEdt->setEchoMode(QLineEdit::Password);
    }
}

void RegistWin::clickCancelBtn()
{
    this->initUI();
    emit RegtoLoginWin();
    this->close();
}

void RegistWin::Regist()
{
    QString account=this->accountEdt->text();
    QString name=this->nameEdt->text();
    QString pwd=this->pwdEdt->text();
//========================表单验证===========================
    if(account.length()==0)
    {
        QMessageBox::warning(this,"注册提示","账号不能为空");
        this->initUI();
        return;
    }
    else if(name.length()==0)
    {
        QMessageBox::warning(this,"注册提示","昵称不能为空");
        this->initUI();
        return;
    }
    else if (this->pwdEdt->text().length()==0) {
        QMessageBox::warning(this,"注册提示","密码不能为空");
        this->initUI();
        return;
    }
    else if (this->cfpwdEdt->text().length()==0) {
        QMessageBox::warning(this,"注册提示","确认密码不能为空");
        this->initUI();
        return;
    }
//=============================注册的实现===========================================
    if(this->pwdEdt->text()==this->cfpwdEdt->text())//输入的密码与确认密码一致
    {
        pwd=GetMd5::str2MD5(pwd);
        int res=UserController::getInstance()->userRegist(account,name,pwd);
        if(res==0)
        {
            QMessageBox::information(this,"注册提示","<font color='red'>注册成功!</font>");
            this->initUI();
            emit back2Login(account);
            int Uid=UserController::getInstance()->getUserIdByAccount(account);
            QDateTime nowTime;
            QString timestr=nowTime.currentDateTime().toString("yyyyMMddHHmmss");
            LogController::getInstance()->addLog(Uid,name,timestr,tr("注册"));
        }
        else if (res==1) {
            QMessageBox::critical(this,"注册提示","<font color='red'>用户名已存在！</font>");
            return;
        }
        else
        {
            QMessageBox::critical(this,"注册提示","<font color='red'>注册失败！</font>");
            return;
        }
    }
    else {
            QMessageBox::critical(this,"注册提示","<font color='red'>两次输入的密码不一致！</font>");
    }
}
