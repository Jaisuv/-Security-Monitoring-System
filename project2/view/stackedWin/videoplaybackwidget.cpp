#include "videoplaybackwidget.h"
#include <QPixmap>
#include <QMovie>
#include <QSize>
#include <QIcon>
#include <QMessageBox>

VideoPlaybackWidget::VideoPlaybackWidget(QWidget *parent) : QWidget(parent)
{
    this->videoId=-1;
    this->calendarisOpen=false;
    this->currentPage=1;
    this->totalPage=1;
    this->initCtrl();
    this->initConnect();
    this->playPrepare();
}

void VideoPlaybackWidget::initCtrl()
{
    this->entireLayout=new QHBoxLayout;
//===================================左边布局播放视频============================================
    this->leftWidget=new QWidget(this);
    this->leftWidget->setObjectName("leftWidget");
    this->leftWidget->setStyleSheet("background:#2e2f33;border:3px solid gray");
    this->leftLayout=new QVBoxLayout;
    //播放最新视频
    this->latestVideo=new QLabel(this->leftWidget);
    this->latestVideo->setObjectName("latestVideo");
    this->latestVideo->setFixedSize(750,500);
    this->latestVideo->setPixmap(QPixmap(":/images/noCamera.png"));
    this->latestVideo->setAlignment(Qt::AlignCenter);
    this->latestVideo->setScaledContents(1);//label上的图片根据Label大小进行自适应
    this->leftLayout->addWidget(this->latestVideo);
    this->leftLayout->setAlignment(Qt::AlignCenter);
    this->leftWidget->setLayout(this->leftLayout);
//================================视频列表Widget===================================
    this->rightWidget=new QWidget(this);
    this->rightWidget->setObjectName("rightWidget_of_videoPlay");
    this->rightLayout=new QVBoxLayout(this);//右边总体是垂直布局
//==========================根据日期查询==================================
    this->searchLayout=new QHBoxLayout(this);

    this->searchNote=new QLabel("请选择要查询的日期:",this->rightWidget);
    this->searchNote->setStyleSheet("color:#e6e6e6; font-size:20px; font-weight:bold");

    this->dateEdt=new QDateEdit(this->rightWidget);
    this->dateEdt->setStyleSheet("height:25px;font-weight:bold;");
    this->dateEdt->setDateTime(QDateTime::currentDateTime());
    this->dateEdt->setCalendarPopup(true);

    this->searchLayout->addWidget(this->searchNote);
    this->searchLayout->addWidget(this->dateEdt);
    this->searchLayout->addStretch(1);
    this->searchLayout->setMargin(5);
    this->searchLayout->setSpacing(3);
//=================================视频列表LW==========================
    this->videoListWiget=new QListWidget(this->rightWidget);
    this->videoListWiget->setObjectName("videoListWidget");
    this->videoListWiget->setViewMode(QListWidget::IconMode);//上图下文
    this->videoListWiget->setIconSize(QSize(230,130));
    this->videoListWiget->setSpacing(5);
    this->videoListWiget->setResizeMode(QListView::Adjust);
    this->videoListWiget->setMovement(QListWidget::Static);
    this->videoListWiget->setGridSize(QSize(250,160));
    this->videoListWiget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->videoListWiget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//=================================翻页按钮水平布局===============
    this->buttonLayout=new QHBoxLayout(this);

    this->PgUp=new QPushButton(tr("上一页"),this->rightWidget);
    this->PgUp->setObjectName("PgUp");

    this->pageLab=new QLabel(tr("%1/%2").arg(this->currentPage).arg(this->totalPage),this->rightWidget);
    this->pageLab->setObjectName("pageLab");

    this->PgDn=new QPushButton(tr("下一页"),this->rightWidget);
    this->PgDn->setObjectName("PgDn");
    //=====8月8日 2:42====
    this->initData();
    //=============
    this->buttonLayout->addWidget(this->PgUp);
    this->buttonLayout->addWidget(this->pageLab);
    this->buttonLayout->addWidget(this->PgDn);
    this->buttonLayout->setAlignment(Qt::AlignHCenter);
    this->buttonLayout->setMargin(5);
    this->buttonLayout->setSpacing(10);
//===================================================================
    this->rightLayout->addLayout(this->searchLayout);
    this->rightLayout->addWidget(this->videoListWiget);
    this->rightLayout->addLayout(this->buttonLayout);
    this->rightWidget->setLayout(this->rightLayout);
    this->rightLayout->setMargin(0);
    this->rightLayout->setSpacing(1);
//=======================整体====================================
    this->entireLayout->addWidget(this->leftWidget,2);
    this->entireLayout->addWidget(this->rightWidget,1);
    this->entireLayout->setMargin(0);
    this->entireLayout->setSpacing(0);
    this->setLayout(this->entireLayout);
}

void VideoPlaybackWidget::initData()
{
    this->currentPage=1;
    QDate today=this->dateEdt->date();
    QString theDayStr=today.toString("yyyyMMdd");
    int num=VideoController::getInstance()->getVideoNumByDate(theDayStr);//获取今天视频总数
    this->totalPage=num/4;//总页数
    int res=num%4;//是否有余数
    if(res!=0)
    {
        this->totalPage++;
    }
    this->videoList=VideoController::getInstance()->getVideoListByDate(theDayStr,(this->currentPage-1)*4);
    //=========================================以上8月8日凌晨3点34===================================
    this->videoListWiget->clear();
    for(int i=0;i<this->videoList.size();i++)
    {
        QString Path=videoList.at(i)->getVideo_path()+'/';
        QListWidgetItem *item=new QListWidgetItem(QIcon(Path+videoList[i]->getCover_name()),
                                                  videoList.at(i)->getVideo_name());
        item->setData(Qt::UserRole,this->videoList.at(i)->getVideo_id());//
        this->videoListWiget->addItem(item);
    }
    this->pageLab->setText(tr("%1/%2").arg(this->currentPage).arg(this->totalPage));
}

void VideoPlaybackWidget::initConnect()
{
    connect(this->PgUp,SIGNAL(clicked()),this,SLOT(PageUp()));
    connect(this->PgDn,SIGNAL(clicked()),this,SLOT(PageDown()));
    connect(this->videoListWiget,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(PlaybackVideo(QListWidgetItem *)));
    connect(this->dateEdt,SIGNAL(dateChanged(QDate)),this,SLOT(refreshList(QDate)));
}

void VideoPlaybackWidget::playPrepare()
{
    MyVideo* LatestVideo=VideoController::getInstance()->getLatest();
    if(LatestVideo==nullptr)
    {
        QMessageBox::warning(nullptr,"视频提示",tr("<font color='red'>没有最新的视频</font>"));
        return;
    }
    QString fileFinal=LatestVideo->getVideo_path()+"/"+LatestVideo->getVideo_name();

    this->replayH264=new RePlayH264(fileFinal);
    this->replayH264->start();
    connect(this->replayH264,SIGNAL(sendImg3(QImage)),this,SLOT(getImage(QImage)));
    connect(this->replayH264,SIGNAL(playFinish()),this,SLOT(restartVideo()));
}


void VideoPlaybackWidget::PageUp()
{
    QDate theDay=this->dateEdt->date();
    QString theDayStr=theDay.toString("yyyyMMdd");
//========================以上测试于8月8日凌晨3点=====================
    if(this->currentPage==1)
    {
        QMessageBox::warning(nullptr,"警告",tr("<font color='red' size='5'>已经是第一页！</font>"));
        return;
    }
    this->currentPage--;
    this->videoList=VideoController::getInstance()->getVideoListByDate(theDayStr,(this->currentPage-1)*4);
    this->videoListWiget->clear();
    for(int i=0;i<this->videoList.size();i++)
    {
        QString Path=videoList.at(i)->getVideo_path()+'/';
        QListWidgetItem *item=new QListWidgetItem(QIcon(Path+videoList[i]->getCover_name()),
                                                  videoList.at(i)->getVideo_name());
        item->setData(Qt::UserRole,this->videoList.at(i)->getVideo_id());
        this->videoListWiget->addItem(item);
    }
    this->pageLab->setText(tr("%1/%2").arg(this->currentPage).arg(this->totalPage));
}

void VideoPlaybackWidget::PageDown()
{
    //====================更新8月8日 3:05====================
    QDate theDay=this->dateEdt->date();
    QString theDayStr=theDay.toString("yyyyMMdd");
    this->currentPage++;
    if(this->currentPage>this->totalPage)
    {
        this->currentPage--;
        QMessageBox::warning(nullptr,"警告",tr("<font color='red' size='5'>已经是最后一页！</font>"));
        return;
    }
    this->videoList=VideoController::getInstance()->getVideoListByDate(theDayStr,(this->currentPage-1)*4);
    this->videoListWiget->clear();
    for(int i=0;i<this->videoList.size();i++)
    {
        QString Path=videoList.at(i)->getVideo_path()+'/';
        QListWidgetItem *item=new QListWidgetItem(QIcon(Path+videoList[i]->getCover_name()),
                                                  videoList.at(i)->getVideo_name());
        item->setData(Qt::UserRole,this->videoList.at(i)->getVideo_id());
        this->videoListWiget->addItem(item);
    }
    this->pageLab->setText(tr("%1/%2").arg(this->currentPage).arg(this->totalPage));
}


/************************************************************
* 函数名称：视频回放播放
* 函数功能：
* 参   数:
* 返 回 值:
**************************************************************/
void VideoPlaybackWidget::PlaybackVideo(QListWidgetItem* videoClicked)
{
    QString videoName=videoClicked->text();
    videoId=videoClicked->data(Qt::UserRole).toInt();
    QString videoPath=VideoController::getInstance()->getVideoPathByName(videoName);
    QString videoFileName=videoPath+"/"+videoName;
    this->playWin=new PlayerWidget(videoFileName,videoId);
    this->playWin->show();
    connect(this->playWin,SIGNAL(successShotscreen()),this,SIGNAL(playerDoScreenShot()));
}

void VideoPlaybackWidget::refreshList(QDate date)
{
    this->currentPage=1;//更新置1
    QString videoDate =date.toString("yyyyMMdd");//选中日期字符串
    this->videoList=VideoController::getInstance()->getVideoListByDate(videoDate,0);//获取那天最后的4条记录
    int videoNum=VideoController::getInstance()->getVideoNumByDate(videoDate);//那天记录数量
    if(videoNum==0)
    {
        this->videoListWiget->clear();
        QMessageBox::warning(nullptr,"查询提示",tr("<font color='red'>没有数据</font>"));
        return;
    }
    this->videoListWiget->clear();
    for(int i=0;i<this->videoList.size();i++)
    {
        QString Path=videoList.at(i)->getVideo_path()+'/';
        QListWidgetItem *item=new QListWidgetItem(QIcon(Path+videoList[i]->getCover_name()),
                                                  videoList.at(i)->getVideo_name());
        item->setData(Qt::UserRole,this->videoList.at(i)->getVideo_id());
        this->videoListWiget->addItem(item);
    }
    this->totalPage=videoNum/4;
    if(videoNum%4!=0)
    {
        this->totalPage++;
    }
    this->pageLab->setText(tr("%1/%2").arg(1).arg(this->totalPage));
}

void VideoPlaybackWidget::getImage(QImage img)
{
    QPixmap receivedImg=QPixmap::fromImage(img);    //接收img
    QSize labSize=this->latestVideo->size();
    QPixmap scaledPixmap=receivedImg.scaled(labSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->latestVideo->setScaledContents(true);
    this->latestVideo->setPixmap(scaledPixmap);
}

void VideoPlaybackWidget::restartVideo()
{
    this->playPrepare();
}






