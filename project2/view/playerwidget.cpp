#include "playerwidget.h"
#include <QFile>
#include <QDebug>
#include <QListView>
#include <QtCore/qmath.h>
#include <QDateTime>
#include <QMessageBox>

PlayerWidget::PlayerWidget(QString videoFile,int vId)
{
//    this->threadFile=videoFile;
    this->videoId=vId;
    this->isPlay=false;
    this->icon1=QIcon(":/images/start_icon.png");
    this->icon2=QIcon(":/images/stop_icon.png");
    this->isPlay=false;
    this->setObjectName("PlayerWin");
    this->setStyleSheet("background:#2e2f33;");
    this->setFixedSize(1300,860);
    this->initCtrl();
    this->loadQSS();
    this->initConnect();

    this->playH264Thread=new PlayH264(videoFile);
//    this->playH264Thread->start();
//    connect(this->playH264Thread,SIGNAL(sendImg2(QImage)),this,SLOT(receiveImg(QImage)));
    QString videoPath=VideoController::getInstance()->getVideoPathById(this->videoId)+"/";
    QString videoName=VideoController::getInstance()->getVideoNameById(this->videoId);
    QString coverPath=VideoController::getInstance()->getVideoCoverById(this->videoId);
    this->videoPlayLab->setPixmap(QPixmap(videoPath+coverPath));
}

void PlayerWidget::initCtrl()
{
    this->entireLayout=new QVBoxLayout(this);

    this->line1Layout=new QHBoxLayout(this);
    this->logoLab=new QLabel(this);
    this->logoLab->setObjectName("logoLab");
    this->logoLab->setFixedSize(50,50);
    this->logoLab->setPixmap(QPixmap(":/images/mainlogo.png").scaled(50,50));

    this->systemNameLab=new QLabel(tr("安防监控系统"),this);
    this->systemNameLab->setStyleSheet("color:white; font-size:20px;font-weight:bold");

    this->line1Layout->addWidget(this->logoLab);
    this->line1Layout->addWidget(this->systemNameLab);
    this->line1Layout->addStretch(1);
    this->line1Layout->setMargin(10);
    this->line1Layout->setSpacing(15);
//=================中间播放器和滑动条=====================
    this->middleLayout=new QVBoxLayout(this);
    this->videoPlayLab=new QLabel(this);
    this->videoPlayLab->setObjectName("videoPlayLab");
//    this->videoPlayLab->setStyleSheet("background:yellow");
//    this->processSlider=new QSlider(Qt::Horizontal);
//    this->processSlider->setObjectName("processSlider");
    this->middleLayout->addWidget(this->videoPlayLab);
//    this->middleLayout->addWidget(this->processSlider);
    this->middleLayout->setMargin(10);
    this->middleLayout->setSpacing(0);
//==================底部按钮布局=======================
    this->line3Layout=new QHBoxLayout(this);

    this->previousBtn=new QPushButton(this);
    this->previousBtn->setStyleSheet("background:transparent;\
                                     border:1px solid gray;");
    this->previousBtn->setFixedSize(30,30);
    this->previousBtn->setIcon(QIcon(":/images/24gf-previous.png"));//播放按钮
    this->previousBtn->setIconSize(QSize(30,30));

    this->swithBtn=new QPushButton(this);
    this->swithBtn->setObjectName("swithBtn");
    this->swithBtn->setStyleSheet("background:#2e2f33;\
                                  border:1px solid gray;\
                                  color:black;\
                                  font-size:18px;\
                                  font-weight:bold;");
    this->swithBtn->setFixedSize(30,30);
    this->swithBtn->setIcon(this->icon1);//播放按钮
    this->swithBtn->setIconSize(QSize(30,30));

    this->nextBtn=new QPushButton(this);
    this->nextBtn->setStyleSheet("background:transparent;\
                                border:1px solid gray;");
    this->nextBtn->setFixedSize(30,30);
    this->nextBtn->setIcon(QIcon(":/images/24gf-next.png"));//播放按钮
    this->nextBtn->setIconSize(QSize(30,30));

    this->speedBox=new QComboBox(this);
    this->speedBox->addItem("0.5x");
    this->speedBox->addItem("1.0x");
    this->speedBox->addItem("2.0x");
    this->speedBox->setCurrentIndex(1);
    //====================下拉框样式==============-
    QString str1 = "QComboBox\
    \n{\
      font-size:20px;\n\
      background:#87ceeb;\n\
      width:60px;\n\
      height:30px;\n\
    }";
    QString str2 = "QComboBox QAbstractItemView\
    {\
      height:40px; \
      font-size:20px;\n\
      background:white;\n\
    }";
    QListView* listView1 = new QListView(this);
//=======================================================
    this->speedBox->setView(listView1);
    this->speedBox->setStyleSheet(str1+str2);

    this->exportBtn=new QPushButton(tr("导出"),this);
    this->exportBtn->setStyleSheet("background:#87ceeb;\
                                       color:black;\
                                       font-size:18px;\
                                       font-weight:bold;");

    this->shotscreenBtn=new QPushButton(tr("截屏"),this);
    this->setObjectName("shotscreenBtn");
    this->shotscreenBtn->setStyleSheet("background:#87ceeb;\
                                       color:black;\
                                       font-size:18px;\
                                       font-weight:bold;");

    this->shotscreenBtn->setFixedSize(60,30);
    this->line3Layout->addWidget(this->previousBtn);
    this->line3Layout->addWidget(this->swithBtn);
    this->line3Layout->addWidget(this->nextBtn);
    this->line3Layout->addStretch(1);
    this->line3Layout->addWidget(this->speedBox);
    this->line3Layout->addWidget(this->exportBtn);
    this->line3Layout->addWidget(this->shotscreenBtn);
    this->line3Layout->setMargin(10);
    this->line3Layout->setSpacing(10);

    this->entireLayout->addLayout(this->line1Layout,1);
    this->entireLayout->addLayout(this->middleLayout,9);
    this->entireLayout->addLayout(this->line3Layout,2);
    this->entireLayout->setMargin(0);
    this->entireLayout->setSpacing(0);
    this->setLayout(this->entireLayout);
}

void PlayerWidget::loadQSS()
{
    QFile playBckqss(":/qss/playBack.qss");
    if(playBckqss.open(QFile::ReadOnly))
    {
        qDebug()<<"Open Successfully!";//qDebug()函数：输出信息
        QString style=QLatin1String(playBckqss.readAll());
        this->setStyleSheet(style);//为窗口设置样式
        playBckqss.close();//打开文件后，要关闭文件
    }
    else
    {
        qDebug()<<"Open Failed!";
    }
}

void PlayerWidget::initConnect()
{
    connect(this->swithBtn,SIGNAL(clicked()),this,SLOT(switchPlay()));
    connect(this->speedBox,SIGNAL(currentIndexChanged(int)),this,SLOT(changeSpeed(int)));
    connect(this->shotscreenBtn,SIGNAL(clicked()),this,SLOT(doShotScreen()));
    connect(this->previousBtn,SIGNAL(clicked()),this,SLOT(toPreVideo()));
    connect(this->nextBtn,SIGNAL(clicked()),this,SLOT(toNextVideo()));
    connect(this->exportBtn,SIGNAL(clicked()),this,SLOT(doExport()));
}

void PlayerWidget::closeEvent(QCloseEvent *event)
{
    if(nullptr==this->playH264Thread)
    {
        event->accept();
        return;
    }
    else {
        this->playH264Thread->terminate();
        delete this->playH264Thread;
        this->playH264Thread=nullptr;
        event->accept();
    }
}

void PlayerWidget::switchPlay()
{
//===============================要在这里start==========================================
    this->playH264Thread->start();
    connect(this->playH264Thread,SIGNAL(sendImg2(QImage)),this,SLOT(receiveImg(QImage)));
//======================================================================================
    this->isPlay=!this->isPlay;
    if(this->isPlay)
    {
        this->playH264Thread->isRun=true;
        this->swithBtn->setIcon(this->icon2);
    }
    else {
        this->playH264Thread->isRun=false;
        this->swithBtn->setIcon(this->icon1);
    }
}

void PlayerWidget::receiveImg(QImage img)
{
    this->videoPlayLab->setPixmap(QPixmap::fromImage(img));
    this->videoPlayLab->setScaledContents(true);
}

void PlayerWidget::changeSpeed(int index)
{
    this->playH264Thread->setSpeedFactor(qPow(2,index));
}

/************************************************************
* 函数名称：
* 函数功能：视频回放截屏以及写入数据库
* 参   数:
* 返 回 值:
**************************************************************/
void PlayerWidget::doShotScreen()
{
    //拍照的存储路径
    QDateTime datetime;
    QString timestr=datetime.currentDateTime().toString("yyyyMMddHHmmss");

    QString photoPath=SettingController::getInstance()->getPhotoPathInDB();
    QString photoName=timestr+".jpg";

    QString photoSaveAddress=photoPath+"/"+photoName;

    QPixmap AframePix=*(this->videoPlayLab->pixmap());
    AframePix.save(photoSaveAddress);
    QMessageBox::information(nullptr,"截屏提醒",tr("<font color='blue'>截屏成功</font>"));
    emit successShotscreen();
    PhotoController::getInstance()->addPhoto(photoName,photoPath,timestr);//写入数据库的操作
}

void PlayerWidget::toPreVideo()
{
    if(this->playH264Thread->isRunning())
    {
        this->playH264Thread->terminate();
        this->isPlay=false;
        this->swithBtn->setIcon(this->icon1);
    }
    this->videoId--;
    if(this->videoId==0)
    {
        QMessageBox::critical(nullptr,tr("切换视频提醒"),tr("<font color='red' size='10'>没有上一个视频</font>"));
        this->videoId++;
        return;
    }
    QString videoPath=VideoController::getInstance()->getVideoPathById(this->videoId)+"/";
    QString videoName=VideoController::getInstance()->getVideoNameById(this->videoId);
    QString coverPath=VideoController::getInstance()->getVideoCoverById(this->videoId);
    this->videoPlayLab->setPixmap(QPixmap(videoPath+coverPath));

    if(this->playH264Thread==nullptr)
    {
        this->playH264Thread=new PlayH264(videoPath+videoName);
        this->playH264Thread->start();
        connect(this->playH264Thread,SIGNAL(sendImg2(QImage)),this,SLOT(receiveImg(QImage)));
    }
    else {
        disconnect(this->playH264Thread,SIGNAL(sendImg2(QImage)),this,SLOT(receiveImg(QImage)));
        delete this->playH264Thread;
        this->playH264Thread=nullptr;
        this->playH264Thread=new PlayH264(videoPath+videoName);
        this->playH264Thread->start();
        connect(this->playH264Thread,SIGNAL(sendImg2(QImage)),this,SLOT(receiveImg(QImage)));
    }
}

void PlayerWidget::toNextVideo()
{
    if(this->playH264Thread->isRunning())
    {
        this->playH264Thread->terminate();
        this->isPlay=false;
        this->swithBtn->setIcon(this->icon1);
    }
    this->videoId++;
    QString videoPath=VideoController::getInstance()->getVideoPathById(this->videoId)+"/";
    QString videoName=VideoController::getInstance()->getVideoNameById(this->videoId);
    if(videoName.isEmpty())
    {
        QMessageBox::critical(nullptr,tr("切换视频提醒"),tr("<font color='red' size='10'>没有下一个视频</font>"));
        this->videoId--;
        return;
    }
    QString coverPath=VideoController::getInstance()->getVideoCoverById(this->videoId);
    this->videoPlayLab->setPixmap(QPixmap(videoPath+coverPath));

    if(this->playH264Thread==nullptr)
    {
        this->playH264Thread=new PlayH264(videoPath+videoName);
        this->playH264Thread->start();
        connect(this->playH264Thread,SIGNAL(sendImg2(QImage)),this,SLOT(receiveImg(QImage)));
    }
    else {
        disconnect(this->playH264Thread,SIGNAL(sendImg2(QImage)),this,SLOT(receiveImg(QImage)));
        delete this->playH264Thread;
        this->playH264Thread=nullptr;
        this->playH264Thread=new PlayH264(videoPath+videoName);
        this->playH264Thread->start();
        connect(this->playH264Thread,SIGNAL(sendImg2(QImage)),this,SLOT(receiveImg(QImage)));
    }
}

void PlayerWidget::doExport()
{
    QString videoPath=VideoController::getInstance()->getVideoPathById(this->videoId)+"/";
    QString videoName=VideoController::getInstance()->getVideoNameById(this->videoId);
    QString coverPath=VideoController::getInstance()->getVideoCoverById(this->videoId);
    this->exportWidget=new ExportWidget(videoPath+videoName);
    this->exportWidget->show();
}









