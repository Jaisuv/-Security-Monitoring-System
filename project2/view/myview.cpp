#include "myview.h"
#include <QIcon>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

MyView::MyView()
{
    //设置大小、背景
    this->setFixedSize(1170,658);
    this->setWindowTitle("开机动画");
    this->setWindowIcon(QIcon(":/images/bootloadwinicon.png"));
    this->setBackgroundBrush(QBrush(QPixmap(":/images/myscene.jpg")));//设置背景

    //创建场景
    this->myScene=new QGraphicsScene(this);
    //设置给当前的视图
    this->setScene(this->myScene);
    //设置场景坐标与视图一致
    this->setSceneRect(0,0,this->width()-2,this->height()-2);

    //创建图元
    this->item1=new MyItem(1,":/images/item1.png");
    //设置图元的位置
    this->item1->setPos(0,this->height()-400);
    //场景添加图元
    this->myScene->addItem(this->item1);

    //创建图元
    this->item2=new MyItem(2,":/images/item2.png");
    //设置图元位置
    this->item2->setPos(1170,this->height()-400);
    //
    this->myScene->addItem(this->item2);

    //创建定时器
    this->timer =new QTimer(this);
    this->timer->start(10);
    //定时器发出时间到了的信号，场景通知图元
    connect(this->timer,SIGNAL(timeout()),this->myScene,SLOT(advance()));
    connect(this->item1,SIGNAL(stopMove()),this,SLOT(stopMove()));

    this->cameras=QCameraInfo::availableCameras();
    //设置界面和主界面都是动画的成员
    this->settingWin =new SettingWin;
    connect(this->settingWin,SIGNAL(setOK(QString,QString,int,QString)),this,SLOT(toMainWin(QString,QString,int,QString)));
    connect(this->settingWin,SIGNAL(settingCancel()),this,SLOT(setC2Main()));
}

MyView::~MyView()
{
    delete this->settingWin;
    delete this->mainWin;
}

void MyView::stopMove()
{
    this->timer->stop();
    this->hide();

    if(SettingController::getInstance()->getSetting()!=0)   //设置表中没数据
    {
        //没数据就直接进入设置界面
        this->settingWin->show();
    }
    else {
        int j=0;
        QString cameraInLib="";
        QString videoPathInLib="";
        QString photoPathInlib="";
        cameraInLib=SettingController::getInstance()->getCameraNameInDB();//得到数据库中的摄像头名称
        videoPathInLib=SettingController::getInstance()->getVideoPathInDB();//得到数据库中的视频路径
        photoPathInlib=SettingController::getInstance()->getPhotoPathInDB();//得到数据库中的照片路径
        //判断摄像头是否存在
        for (j=0;j<this->cameras.size();j++) {
            if(cameras[j].description()==cameraInLib)//摄像头存在
            {
                break;
            }
        }
        if(j==cameras.size())
        {
            qDebug()<<"摄像头不存在,重新设置！";
            this->settingWin->show();
            return;
        }
        //判断视频路径是否存在
        QDir vdir(videoPathInLib);
        if(vdir.exists()==false)//不存在
        {
            qDebug()<<"视频文件夹不存在！";
            this->settingWin->show();
            return;
        }
        //判断照片路径是否存在
        QDir pdir(photoPathInlib);
        if(pdir.exists()==false)//不存在
        {
            qDebug()<<"照片文件夹不存在！";
            this->settingWin->show();
            return;
        }
        this->settingWin->isfirst=false;
        this->mainWin=new MainWin;
        this->mainWin->monitorWidget->openCamera();
        this->mainWin->show();
        connect(this->mainWin,SIGNAL(toSetting()),this,SLOT(showSetting()));
    }
}

//设置界面  按确定后
void MyView::toMainWin(QString video_path,QString photo_path,int capture_interval,QString camera_name)
{
    this->settingWin->hide();
    if(this->settingWin->isfirst)
    {
        this->settingWin->isfirst=false;
        this->mainWin=new MainWin;
        //设置信息写入数据库
        int res=SettingController::getInstance()->updateSetting(video_path,photo_path,capture_interval,camera_name);
        if(SQLITE_OK!=res)
        {
            qDebug()<<tr("设置失败");
            return;
        }
        this->mainWin->monitorWidget->openCamera();
        this->mainWin->show();
        connect(this->mainWin,SIGNAL(toSetting()),this,SLOT(showSetting()));
    }
    else{
        //从主界面进入设置后,如果更新设置了就需要重启，没有更新设置就直接
        QString cameraInLib="";
        QString videoPathInLib="";
        QString photoPathInlib="";
        cameraInLib=SettingController::getInstance()->getCameraNameInDB();//得到数据库中的摄像头名称
        videoPathInLib=SettingController::getInstance()->getVideoPathInDB();//得到数据库中的视频路径
        photoPathInlib=SettingController::getInstance()->getPhotoPathInDB();//得到数据库中的照片路径
        int capIntervalInLib=SettingController::getInstance()->getCapInterval();//得到数据中的采集间隔

        qDebug()<<videoPathInLib<<" "<<photoPathInlib<<" "<<capIntervalInLib<<" "<<cameraInLib;
        qDebug()<<video_path<<" "<<photo_path<<" "<<capture_interval<<" "<<camera_name;


        if(video_path==videoPathInLib && photo_path==photoPathInlib && camera_name==cameraInLib && capIntervalInLib==capture_interval)
        {
            QMessageBox::information(nullptr,tr("设置提醒"),tr("<font color='blue'>设置并未更新</font>"));
            //设置没更新就不需要写入数据库，也不需要重启
        }
        else { //只要有一个更新了就得写入数据库和重启
            QMessageBox::warning(nullptr,tr("设置提醒"),tr("<font color='red'>设置已更新，即将重启</font>"));
            //更新数据库，写入新的设置信息
            int res=SettingController::getInstance()->updateSetting(video_path,photo_path,capture_interval,camera_name);
            if(SQLITE_OK!=res)
            {
                qDebug()<<tr("设置失败");
                return;
            }
            //程序关闭、重启
            Reboot::programReboot();
        }

    }
    this->mainWin->show();
}

//主界面点击系统设置跳出设置界面
void MyView::showSetting()
{
    QString videoPathInLib="";
    QString photoPathInlib="";
    int captureTimeInLib=0;
    QString cameraInLib="";

    videoPathInLib=SettingController::getInstance()->getVideoPathInDB();//得到数据库中的视频路径
    photoPathInlib=SettingController::getInstance()->getPhotoPathInDB();//得到数据库中的照片路径
    captureTimeInLib=SettingController::getInstance()->getCapInterval();
    cameraInLib=SettingController::getInstance()->getCameraNameInDB();

    this->settingWin->setVideoPth(videoPathInLib);
    this->settingWin->setPhotoPth(photoPathInlib);
    this->settingWin->setTimeBox(captureTimeInLib-1);
    this->settingWin->setCameraBox(cameraInLib);

    this->settingWin->show();
}

void MyView::setC2Main()
{
    this->settingWin->hide();
    this->mainWin->show();
}


