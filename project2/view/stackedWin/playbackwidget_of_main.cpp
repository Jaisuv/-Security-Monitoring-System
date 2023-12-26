#include "playbackwidget_of_main.h"
#include <QFile>
#include <QDebug>

PlaybackWidget_of_main::PlaybackWidget_of_main(QWidget *parent) : QWidget(parent)
{
    this->initCtrl();
    this->loadQSS();
    this->initConnect();
}

void PlaybackWidget_of_main::initCtrl()
{
    this->entireLayout=new QHBoxLayout(this);

    this->leftGuide=new QListWidget(this);
    this->leftGuide->setObjectName("leftGuide");
    this->leftGuide->addItem(tr("视频回放"));
    this->leftGuide->addItem(tr("照片列表"));

    this->rightWidget=new QStackedWidget(this);

    this->videoPlaybackWidget=new VideoPlaybackWidget(this);

    this->photoViewerWidget=new PhotoViewerWidget(this);

    this->rightWidget->addWidget(this->videoPlaybackWidget);
    this->rightWidget->addWidget(this->photoViewerWidget);

    this->entireLayout->addWidget(this->leftGuide,1);
    this->entireLayout->addWidget(this->rightWidget,8);
    this->entireLayout->setMargin(0);
    this->entireLayout->setSpacing(0);
    this->setLayout(this->entireLayout);

}

void PlaybackWidget_of_main::loadQSS()
{
    QFile loginqss(":/qss/playback_of_main.qss");
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

void PlaybackWidget_of_main::initConnect()
{
    connect(this->leftGuide,SIGNAL(currentRowChanged(int)),this->rightWidget,SLOT(setCurrentIndex(int)));
    connect(this->videoPlaybackWidget,SIGNAL(playerDoScreenShot()),this,SLOT(refreshPhotoWall()));
}

void PlaybackWidget_of_main::refreshPhotoWall()
{
    this->photoViewerWidget->initData();
}
