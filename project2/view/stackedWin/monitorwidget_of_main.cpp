//监控模式
#include "monitorwidget_of_main.h"
#include <QFile>
#include <QDebug>
#include <QPixmap>
#include <QSize>
#include <QDateTime>
#include <QSizePolicy>
#include <QIcon>
#include <QMessageBox>

MonitorWidget_of_Main::MonitorWidget_of_Main(QWidget *parent) : QWidget(parent)
{
    this->initCtrl();
    this->loadQSS();
    this->initConnect();
}

void MonitorWidget_of_Main::initCtrl()
{
    this->totalLayout=new QHBoxLayout;

    this->deviceListWidget=new QWidget(this);
    this->deviceListWidget->setObjectName("deviceListWidget");
    this->deviceListLayout=new QVBoxLayout;

    this->deviceTitle=new QLabel("设备列表",this);
    this->deviceTitle->setObjectName("deviceTitle");
    this->deviceTitle->setAlignment(Qt::AlignHCenter);//水平居中
    this->deviceListLayout->addWidget(this->deviceTitle);
    //======================设备列表====================================
    this->devicesList=new QListWidget(this);
    this->devicesList->setObjectName("devicesList");
    this->devices=QCameraInfo::availableCameras();
    for (int i=0;i<devices.size();i++) {
        this->devicesList->addItem(devices[i].description());
    }
    this->deviceListLayout->addWidget(this->devicesList);
//=========================设别列表======================================
    this->deviceListLayout->setMargin(2);
    this->deviceListLayout->setSpacing(5);
    this->deviceListLayout->addStretch(1);
    this->deviceListWidget->setLayout(this->deviceListLayout);
    //============================================================
    this->playBlockWidget=new QWidget(this);
    this->playBlockWidget->setObjectName("playBlockWidget");
    this->playBlockLayout=new QVBoxLayout(this);  //布局

    this->fourChannelWidget=new QWidget(this);
    this->fourChannelWidget->setObjectName("fourChannelWidget");
    this->fourChannelLayout=new QGridLayout(this);//四宫格网格布局
    this->video1_label=new QLabel(this);
    this->video1_label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    this->video2_label=new QLabel(this);
    this->video2_label->setStyleSheet("background:green");
    this->video2_label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    this->video2_label->setPixmap(QPixmap(":/images/virtualCamera.png"));
    this->video2_label->setScaledContents(1);

    this->video4_label=new QLabel(this);
    this->video4_label->setStyleSheet("background:blue");
    this->video4_label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    QMovie *movie=new QMovie(":/images/channel3gif.gif");
    this->video4_label->setMovie(movie);
    movie->start();

    this->video3_label=new QLabel(this);
    this->video3_label->setStyleSheet("background:pink");
    this->video3_label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    this->video3_label->setPixmap(QPixmap(":/images/noCamera.png"));
    this->video3_label->setScaledContents(true);

    this->fourChannelLayout->addWidget(video1_label,0,0);
    this->fourChannelLayout->addWidget(video2_label,0,1);
    this->fourChannelLayout->addWidget(video3_label,1,0);
    this->fourChannelLayout->addWidget(video4_label,1,1);

    this->videoLabelList.push_back(this->video1_label);
    this->videoLabelList.push_back(this->video2_label);
    this->videoLabelList.push_back(this->video3_label);
    this->videoLabelList.push_back(this->video4_label);

    this->fourChannelLayout->setSpacing(0);
    this->fourChannelLayout->setMargin(0);
    this->fourChannelWidget->setLayout(fourChannelLayout);
//====================================================================
    this->channelSelectWidget=new QWidget(this);
    this->channelSelectWidget->setObjectName("channelSelectWidget");
    this->channelSelectLayout=new QHBoxLayout(this);//布局

    this->fourChannelBtn=new QPushButton(this);
    this->fourChannelBtn->setObjectName("fourChannelBtn");
    this->fourChannelBtn->setIcon(QIcon(":/images/fourGrid.png"));

    this->channel1Btn=new QPushButton(tr("❶"),this);
    this->channel1Btn->setObjectName("channel1Btn");

    this->channel2Btn=new QPushButton(tr("❷"),this);
    this->channel2Btn->setObjectName("channel2Btn");

    this->channel3Btn=new QPushButton(tr("❸"),this);
    this->channel3Btn->setObjectName("channel3Btn");

    this->channel4Btn=new QPushButton(tr("❹"),this);
    this->channel4Btn->setObjectName("channel4Btn");

    this->screenshotBtn=new QPushButton(tr("拍照"),this);
    this->screenshotBtn->setObjectName("screenshotBtn");

    this->channelSelectLayout->addStretch(1);
    this->channelSelectLayout->addWidget(fourChannelBtn);
    this->channelSelectLayout->addWidget(channel1Btn);
    this->channelSelectLayout->addWidget(channel2Btn);
    this->channelSelectLayout->addWidget(channel3Btn);
    this->channelSelectLayout->addWidget(channel4Btn);
    this->channelSelectLayout->addStretch(1);
    this->channelSelectLayout->addWidget(screenshotBtn);
    this->channelSelectLayout->addStretch(1);
    this->channelSelectLayout->setMargin(10);
    this->channelSelectLayout->setSpacing(10);
    this->channelSelectWidget->setLayout(this->channelSelectLayout);

    this->playBlockLayout->addWidget(this->fourChannelWidget,10);
    this->playBlockLayout->addWidget(this->channelSelectWidget,1);
    this->playBlockLayout->setSpacing(0);
    this->playBlockLayout->setMargin(0);
    this->playBlockWidget->setLayout(this->playBlockLayout);

    this->totalLayout->addWidget(this->deviceListWidget,1);
    this->totalLayout->addWidget(this->playBlockWidget,7);
    this->totalLayout->setSpacing(0);
    this->totalLayout->setMargin(0);
    this->setLayout(this->totalLayout);
    this->isLogin=false;
}

void MonitorWidget_of_Main::loadQSS()
{
    QFile loginqss(":/qss/monitor_of_main.qss");
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

void MonitorWidget_of_Main::openCamera()
{
    QString nowCamera=SettingController::getInstance()->getCameraNameInDB();//得到数据库中的摄像头名称
    this->thread1=new CameraOpenThread(nowCamera);
    this->thread1->start();
    connect(this->thread1,SIGNAL(sendImg(QImage)),this,SLOT(videoChannel1Show(QImage)));
}

QListWidget *MonitorWidget_of_Main::getDevicesList() const
{
    return devicesList;
}

void MonitorWidget_of_Main::setDevicesList(QListWidget *value)
{
    devicesList = value;
}

void MonitorWidget_of_Main::initConnect()
{
    connect(this->screenshotBtn,SIGNAL(clicked()),this,SLOT(screenshot()));
    connect(this->channel1Btn,SIGNAL(clicked()),this,SLOT(toChannel1()));
    connect(this->channel2Btn,SIGNAL(clicked()),this,SLOT(toChannel2()));
    connect(this->channel3Btn,SIGNAL(clicked()),this,SLOT(toChannel3()));
    connect(this->channel4Btn,SIGNAL(clicked()),this,SLOT(toChannel4()));
    connect(this->fourChannelBtn,SIGNAL(clicked()),this,SLOT(form4Channel()));
}

void MonitorWidget_of_Main::videoChannel1Show(QImage img)
{
    QPixmap receivedImg=QPixmap::fromImage(img);    //接收img
    QSize labSize=this->video1_label->size();
    QPixmap scaledPixmap=receivedImg.scaled(labSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->video1_label->setScaledContents(true);
    this->video1_label->setPixmap(scaledPixmap);
}

void MonitorWidget_of_Main::screenshot()
{
    //拍照的存储路径
    QDateTime datetime;
    QString timestr=datetime.currentDateTime().toString("yyyyMMddHHmmss");

    QString photoPath=SettingController::getInstance()->getPhotoPathInDB();
    QString photoName=timestr+".jpg";

    QString photoSaveAddress=photoPath+"/"+photoName;

    int nowCtrlnum=this->fourChannelLayout->count();
    if(this->isLogin && nowCtrlnum==1)
    {
        QPixmap thePixmap;
        //获取单前的通道的图片并保存
        if(videoLabelList.at(channelIndex)->movie()==nullptr){
            thePixmap=*(videoLabelList.at(channelIndex)->pixmap());
        }
        else {
            thePixmap=videoLabelList.at(channelIndex)->movie()->currentPixmap();
        }
        thePixmap.save(photoSaveAddress);
        QMessageBox::information(nullptr,tr("拍照提示"),tr("<font color='blue' size='5'>拍照成功</font>"));
        PhotoController::getInstance()->addPhoto(photoName,photoPath,timestr);
    }
    else if (this->isLogin==false) {
        QMessageBox::warning(nullptr,"拍照提示",tr("<font color='red' size='5'>未登录禁止拍照</font>"));
    }
    else if (nowCtrlnum!=1) {
        QMessageBox::warning(nullptr,"拍照提示",tr("<font color='red' size='5'>请切换到单通道执行拍照</font>"));
    }
}

void MonitorWidget_of_Main::toChannel1()
{
    for(QLabel* label:videoLabelList)
    {
        if(label !=video1_label)
        {
            label->setScaledContents(true);
            label->setParent(nullptr);
        }
        else {
            this->fourChannelLayout->addWidget(label);
        }
    }
    this->channelIndex=0;
}

void MonitorWidget_of_Main::toChannel2()
{
    for(QLabel* label:videoLabelList)
    {
        if(label !=video2_label)
        {
            label->setParent(nullptr);
        }
        else {
            this->fourChannelLayout->addWidget(label);
            label->setScaledContents(true);
            label->setParent(this->fourChannelWidget);
        }
    }
    this->channelIndex=1;
}

void MonitorWidget_of_Main::toChannel3()
{
    for(QLabel* label:videoLabelList)
    {
        if(label !=video3_label)
        {
            label->setScaledContents(true);
            label->setParent(nullptr);
        }
        else {
            this->fourChannelLayout->addWidget(label);
            label->setScaledContents(true);
            label->setParent(this->fourChannelWidget);
        }
    }
    this->channelIndex=2;
}

void MonitorWidget_of_Main::toChannel4()
{
    for(QLabel* label:videoLabelList)
    {
        if(label !=video4_label)
        {
            label->setScaledContents(true);
            label->setParent(nullptr);
        }
        else {
            this->fourChannelLayout->addWidget(label);
            label->setScaledContents(true);
            label->setParent(this->fourChannelWidget);
        }
    }
    this->channelIndex=3;
}

void MonitorWidget_of_Main::form4Channel()
{
    this->fourChannelLayout->addWidget(video1_label,0,0);
    this->fourChannelLayout->addWidget(video2_label,0,1);
    this->fourChannelLayout->addWidget(video3_label,1,0);
    this->fourChannelLayout->addWidget(video4_label,1,1);
    for(QLabel* label:videoLabelList)
    {
        label->setScaledContents(true);
        label->setParent(this->fourChannelWidget);
    }
}
