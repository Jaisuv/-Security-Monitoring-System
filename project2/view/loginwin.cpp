#include "loginwin.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox> //信息提示窗
#include <QTime>
#include <QRegExpValidator> //正则表达式类
#include "tools/getmd5.h"   //加密类
#include <QDateTime>

LoginWin::LoginWin(QWidget *parent) : QWidget(parent)
{
    //设置图标
    this->setWindowIcon(QIcon(":/images/bootloadwinicon.png"));
    //设置标题
    this->setWindowTitle("登录");
    //设置窗口的大小与背景
    this->setGeometry(300,400,600,400);
    this->setObjectName("LoginWin");

    this->icon1=QIcon(":/images/visible.png");
    this->icon2=QIcon(":/images/unvisible.png");
    this->isVisible=false;
    //控件初始化
    this->initControl();
    this->loadQss();
    this->initConnect();//构造函数要添加关联
}

void LoginWin::loadQss()
{
    QFile loginqss(":/qss/login.qss");
    if(loginqss.open(QFile::ReadOnly))
    {
        qDebug()<<"Open Successfully!";//qDebug()函数：输出信息
        QString style=QLatin1String(loginqss.readAll());
        this->setStyleSheet(style);//为窗口设置样式
        loginqss.close();//打开文件后，要关闭文件
    }
    else
    {
        qDebug()<<"Open Failed!";
    }
}

void LoginWin::initControl()
{
    this->title=new QLabel("登录",this);
    this->title->setObjectName("title");
    this->title->move(260,30);

    this->accountLab=new QLabel(" 账 号：",this);
    this->accountLab->move(130,100);

    this->accountEdt=new QLineEdit(this);
    this->accountEdt->move(210,90);
    this->accountEdt->setPlaceholderText("请输入账号");
    QRegExp regExp1("[0-9a-zA-Z]{6,}");//创建正则表达式模式 最少要6位数字和英文大小写字母
    QRegExpValidator *validator1=new QRegExpValidator(regExp1,this);//创建验证器并设置正则表达式模式
    this->accountEdt->setValidator(validator1);//将上述验证器应用于用户名输入框
    this->accountEdt->setMaxLength(10);

    this->pwdLab=new QLabel(" 密 码：",this);
    this->pwdLab->move(130,170);

    this->pwdEdt=new QLineEdit(this);
    this->pwdEdt->move(210,160);
    this->pwdEdt->setPlaceholderText("请输入密码");
    QRegExp regExp2("[0-9a-zA-Z]{6,}");//创建正则表达式模式 最少要6位数字
    QRegExpValidator *validator2=new QRegExpValidator(regExp2,this);
    this->pwdEdt->setValidator(validator2);
    this->pwdEdt->setMaxLength(10);
    this->pwdEdt->setEchoMode(QLineEdit::Password);

    this->pwdChangeBtn=new QPushButton(this);
    this->pwdChangeBtn->setObjectName("pwdChangeBtn");
    this->pwdChangeBtn->move(383,160);
    this->pwdChangeBtn->setIcon(this->icon2);
    this->pwdChangeBtn->setIconSize(QSize(30,30));

    this->codeLab=new QLabel("验证码：",this);
    this->codeLab->move(130,240);

    this->codeEdt=new QLineEdit(this);
    this->codeEdt->move(210,230);
    this->codeEdt->setPlaceholderText("4位验证码");
    QRegExp regExp3("[0-9a-zA-Z]{4,}");//创建正则表达式模式 最少要4位数字和英文大小写字母
    QRegExpValidator *validator3=new QRegExpValidator(regExp3,this);//创建验证器并设置正则表达式模式
    this->codeEdt->setValidator(validator3);//将上述验证器应用于用户名输入框
    this->codeEdt->setMaxLength(4);
    //行内样式
    this->codeEdt->setStyleSheet("width:100px;height:36px;border:none;border-radius:4px;");

    this->veriBtn=new Verification(this);
    this->veriBtn->move(320,230);
    this->veriBtn->setStyleSheet("width:100px;height:36px;");

    this->loginBtn=new QPushButton("登录",this);
    this->loginBtn->move(160,300);
    this->loginBtn->setFont(QFont("宋体",18,700));

    this->quitBtn=new QPushButton("取消",this);
    this->quitBtn->move(350,300);
    this->quitBtn->setFont(QFont("宋体",18,700));

    this->toRegistBtn=new QPushButton("去注册",this);
    this->toRegistBtn->move(20,350);
    //设置背景透明的按钮
    this->toRegistBtn->setStyleSheet("width:100px;height:40px;background:transparent;border:none;color:white;border-radius:12px");

    this->regWin=new RegistWin;
}

void LoginWin::initConnect()
{
    connect(this->toRegistBtn,SIGNAL(clicked()),this,SLOT(toRegistWin()));
    connect(this->pwdChangeBtn,SIGNAL(clicked()),this,SLOT(changeEchoMode()));
    connect(this->regWin,SIGNAL(RegtoLoginWin()),this,SLOT(showSelf()));
    connect(this->loginBtn,SIGNAL(clicked()),this,SLOT(doLogin()));
    connect(this->veriBtn,SIGNAL(clicked()),this,SLOT(getCode()));
    connect(this->quitBtn,SIGNAL(clicked()),this,SLOT(doQuit()));
    connect(this->regWin,SIGNAL(back2Login(QString)),this,SLOT(Reg2Log(QString)));
}

void LoginWin::getCode()
{
    this->codenum=this->veriBtn->generateRandNum();
}

void LoginWin::doLogin()
{
    //先判断验证码
    QString codestr= this->codeEdt->text(); //获取输入的验证码
    if(codestr.size()==0)
    {
//        QMessageBox::warning(this,"登录提醒","<font color='red'>验证码不能为空!</font>");
        QMessageBox::warning( nullptr,"登录提醒","验证码不能为空!");
        return ;
    }
    else if(codestr.size()<4)
    {
        QMessageBox::warning(this,"登录提醒","<font color='red'>验证码必须为4位!</font>");
        return;
    }
    else if(codestr!=this->codenum)
    {
        QMessageBox::critical(this,"登录提醒","<font color='red'>请输入正确的验证码!</font>");
        this->codeEdt->clear();//清空验证码编辑框
        emit this->veriBtn->clicked();
        return ;
    }

    QString account=this->accountEdt->text();//获取输入的账号
    QString pwd=this->pwdEdt->text();//获取输入的密码
    pwd=GetMd5::str2MD5(pwd);//加密
    if(account.size()==0)
    {
        QMessageBox::warning(this,"登录提醒","<font color='red'>账号不能为空!</font>");
        return ;
    }
    else if(account.size()<6)
    {
        QMessageBox::warning(this,"登录提醒","<font color='red'>账号最少要6位!</font>");
        return ;
    }

    if(pwd.size()==0)
    {
        QMessageBox::warning(this,"登录提醒","<font color='red'>密码不能为空!</font>");
        return ;
    }
    else if(pwd.size()<6)
    {
         QMessageBox::warning(this,"登录提醒","<font color='red'>密码最少要6位!</font>");
         return ;
    }

    int res=UserController::getInstance()->Login(account,pwd);
    if(res==0)
    {
        //控制器登录获得登录成功会执行更新操作
        QMessageBox::information(this,"登录提示",tr("<font color='blue'>登录成功！你好！%1</font>").arg(account));
        QString Uname=UserController::getInstance()->getUserName(account);
        int Uid=UserController::getInstance()->getUserIdByAccount(account);
        QDateTime datetime;
        QString timestr=datetime.currentDateTime().toString("yyyyMMddHHmmss");
        LogController::getInstance()->addLog(Uid,Uname,timestr,tr("登录"));
        Uname=tr("你好,")+Uname;
        emit this->LogInSuccess(Uname);
        this->accountEdt->clear();
        this->pwdEdt->clear();
        this->codeEdt->clear();
    }
    else
    {
        QMessageBox::critical(this,"登录提示","<font color='red'>登录失败！</font>");
    }
}

void LoginWin::doQuit()
{
    this->accountEdt->clear();
    this->pwdEdt->clear();
    this->codeEdt->clear();
    this->close();
}

void LoginWin::toRegistWin()
{
    this->hide();
    this->regWin->show();
}

void LoginWin::showSelf()
{
    this->show();
}

void LoginWin::Reg2Log(QString newAccount)
{

    this->regWin->close();
    this->accountEdt->setText(newAccount);
    this->pwdEdt->clear();
    this->codeEdt->clear();
    this->show();
}

void LoginWin::changeEchoMode()
{
    this->isVisible=!this->isVisible;
    if(this->isVisible)
    {
        this->pwdChangeBtn->setIcon(this->icon1);
        this->pwdEdt->setEchoMode(QLineEdit::Normal);
    }
    else {
        this->pwdChangeBtn->setIcon(this->icon2);
        this->pwdEdt->setEchoMode(QLineEdit::Password);
    }
}

