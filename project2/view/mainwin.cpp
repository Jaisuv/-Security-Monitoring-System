#include "mainwin.h"
#include <QPixmap>
#include <QPicture>
#include <QSize>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QMessageBox>

MainWin::MainWin(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("主界面");
    //设置图标
    this->setWindowIcon(QIcon(":/images/bootloadwinicon.png"));
    //设置窗口的大小与背景
//    this->resize(1300,860);
    this->setFixedSize(1300,860);
    this->setObjectName("LoginWin");
    this->initUi();
    this->initConnect();
    this->loadQSS();
    startTimer(1000);
}

MainWin::~MainWin()
{
    delete this->SigninWidget;
}

void MainWin::initUi()
{
    this->mainlayout=new QVBoxLayout;
    //==================================
    this->guideWidget=new QWidget(this);
    this->guideWidget->setObjectName("guideWidget");
    this->guideLayout=new QHBoxLayout(this);

    QPixmap pixmap(":/images/mainlogo.png");
    this->logoLab=new QLabel(this);
    this->logoLab->resize(50,50);
    QSize Labsize=this->logoLab->size();
    QPixmap scaledPixmap = pixmap.scaled(Labsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->logoLab->setPixmap(scaledPixmap);
    this->guideLayout->addWidget(this->logoLab);

    this->titleLab=new QLabel("安防监控系统",this);
    this->titleLab->setObjectName("titleLab");
    this->guideLayout->addWidget(this->titleLab,1);

    this->monitorBtn=new QPushButton("视频监控",this);
    this->guideLayout->addWidget(this->monitorBtn);

    this->playbackBtn=new QPushButton("视频回放",this);
    this->guideLayout->addWidget(this->playbackBtn);

    this->logBtn=new QPushButton("日志查询",this);
    this->guideLayout->addWidget(this->logBtn);

    this->settingBtn=new QPushButton("系统设置",this);
    this->guideLayout->addWidget(this->settingBtn);

    this->loginBtn=new QPushButton("登录",this);
    this->loginBtn->setObjectName("loginBtn");
    this->guideLayout->addWidget(this->loginBtn);

    //只是创建了这个按钮，并没有添加到布局当中
    this->logoutBtn=new QPushButton("",this);
    this->logoutBtn->setObjectName("logoutBtn");
    this->guideLayout->addWidget(this->logoutBtn);

    this->timeLab=new QLabel("系统时间",this);
    this->timeLab->setObjectName("timeLab");
    this->guideLayout->addWidget(this->timeLab);

    this->guideWidget->setLayout(this->guideLayout);
    //================================================
    this->widgetStack=new QStackedWidget(this);

    this->monitorWidget=new MonitorWidget_of_Main(this);
    this->widgetStack->addWidget(this->monitorWidget);

    this->playbackWidget=new PlaybackWidget_of_main(this);
    this->widgetStack->addWidget(this->playbackWidget);

    this->logTablUI=new LogTabelWidget(this);
    this->widgetStack->addWidget(this->logTablUI);
    //===================================================
    this->mainlayout->addWidget(this->guideWidget,1);
    this->mainlayout->addWidget(this->widgetStack,9);
    this->mainlayout->setMargin(0);
    this->mainlayout->setSpacing(0);
    this->setLayout(this->mainlayout);

    this->SigninWidget=new LoginWin;
    this->logoutBtn->hide();
}

void MainWin::initConnect()
{
    connect(this->monitorBtn,SIGNAL(clicked()),this,SLOT(showMonitor()));
    connect(this->playbackBtn,SIGNAL(clicked()),this,SLOT(showPlayback()));
    connect(this->logBtn,SIGNAL(clicked()),this,SLOT(showLog()));
    connect(this->loginBtn,SIGNAL(clicked()),this,SLOT(showSignIn()));
    connect(this->settingBtn,SIGNAL(clicked()),this,SIGNAL(toSetting()));
    connect(this->SigninWidget,SIGNAL(LogInSuccess(QString)),this,SLOT(LoginSuccess(QString)));
    connect(this->logoutBtn,SIGNAL(clicked()),this,SLOT(Logout()));
}

void MainWin::loadQSS()
{
    QFile mainqss(":/qss/main.qss");
    if(mainqss.open(QFile::ReadOnly))
    {
        qDebug()<<"Open Successfully!";//qDebug()函数：输出信息
        QString style=QLatin1String(mainqss.readAll());
        this->setStyleSheet(style);//为窗口设置样式
        mainqss.close();//打开文件后，要关闭文件
    }
    else
    {
        qDebug()<<"Open Failed!";
    }
}

QPushButton *MainWin::getLogoutBtn() const
{
    return logoutBtn;
}

void MainWin::setLogoutBtn(QPushButton *value)
{
    logoutBtn = value;
}

void MainWin::timerEvent(QTimerEvent *event)
{
    QDateTime current_time = QDateTime::currentDateTime(); //获取当前时间
    //    QDate date;
    //    QString datestr=date.toString("");
    //显示时间，格式为：年-月-日 时:分:秒
//    QString StrCurrentTime = current_time.toString("yyyy/MM/dd hh:mm:ss");
    QString StrCurrentTime = current_time.toString(" hh:mm:ss");
    this->timeLab->setText(StrCurrentTime);
}

void MainWin::showMonitor()
{
    this->widgetStack->setCurrentIndex(0);
}

void MainWin::showPlayback()
{
//    if(this->logoutBtn->text()=="")
//    {
//        QMessageBox::warning(nullptr,"模式切换警告",tr("<font color='red' size='5'>请先登录</font>"));
//        return;
//    }
//    if(this->logoutBtn->text()=="")
//    {
//        QMessageBox::warning(nullptr,"进入回放提醒",tr("<font color='red' size='5'>没有回放数据！</font>"));
//        return;
//    }
    this->widgetStack->setCurrentIndex(1);
    this->playbackWidget->videoPlaybackWidget->initData();
    this->playbackWidget->photoViewerWidget->initData();
}

void MainWin::showLog()
{
//    if(this->logoutBtn->text()=="")
//    {
//        QMessageBox::warning(nullptr,"模式切换警告",tr("<font color='red' size='5'>请先登录</font>"));
//        return;
//    }
    this->widgetStack->setCurrentIndex(2);
    this->logTablUI->initData();
}

void MainWin::showSignIn()
{
    this->SigninWidget->show();
}

void MainWin::LoginSuccess(QString name)
{
    this->SigninWidget->hide();
    this->loginBtn->hide();
    this->logoutBtn->setText(name);
    this->monitorWidget->isLogin=true;
    this->logoutBtn->show();
}

void MainWin::Logout()//登出并改变状态
{
    QMessageBox::warning(nullptr,tr("退出提醒"),tr("<font color='red'>确认退出</font>"));
    QString user_name="";
    user_name=this->logoutBtn->text();
    user_name=user_name.replace("你好,","");
    QString Account=UserController::getInstance()->getUserAccount(user_name);
    this->logoutBtn->setText("");
    UserController::getInstance()->Logout(Account);
    int Uid=UserController::getInstance()->getUserIdByAccount(Account);
    QDateTime datetime;
    QString timestr=datetime.currentDateTime().toString("yyyyMMddHHmmss");
    LogController::getInstance()->addLog(Uid,user_name,timestr,tr("注销"));
    this->logoutBtn->hide();
    this->loginBtn->show();
    this->monitorWidget->isLogin=false;
    this->widgetStack->setCurrentIndex(0);
}
