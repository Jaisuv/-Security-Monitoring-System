#include "settingwin.h"
#include <QIcon>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QCameraInfo>
#include <QMessageBox>

SettingWin::SettingWin(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("设置界面");   //窗口标题
    this->setWindowIcon(QIcon(":/images/bootloadwinicon.png")); //窗口图标
    this->setGeometry(700,300,720,500);   //窗口的位置和大小
    this->setObjectName("settingWin");
    this->cameras=QCameraInfo::availableCameras();
    this->initCtrl();
    this->loadQSS();
    this->initConnect();
    this->isfirst=true;
}

void SettingWin::initCtrl()
{
    this->title=new QLabel("设置界面",this);
    this->title->move(270,45);
    this->title->setObjectName("title");

    this->videoPthLab=new QLabel("视频存储路径",this);
    this->videoPthLab->move(140,120);

    this->photoPthLab=new QLabel("图片存储路径",this);
    this->photoPthLab->move(140,180);

    this->time_interval=new QLabel("采集时间间隔",this);
    this->time_interval->move(140,240);

    this->camera_setting=new QLabel(" 摄像头配置",this);
    this->camera_setting->move(142,300);

    this->okBtn=new QPushButton("确定",this);
    this->okBtn->move(200,360);

    this->cancelBtn=new QPushButton("取消",this);
    this->cancelBtn->move(400,360);

    this->videoPthEdt=new QLineEdit(this);
    this->videoPthEdt->move(250,115);
    this->videoPthEdt->setReadOnly(true);   //只读模式，无法输入

    this->photoPthEdt=new QLineEdit(this);
    this->photoPthEdt->move(250,175);
    this->photoPthEdt->setReadOnly(true);

    this->timeBox=new QComboBox(this);
    this->timeBox->move(250,234);
    this->timeBox->addItem("1分钟");
    this->timeBox->addItem("2分钟");
    this->timeBox->addItem("3分钟");

    this->cameraBox=new QComboBox(this);
    this->cameraBox->move(250,294);
    if(cameras.size()<=0)
    {
        qDebug()<<"no available camera";
        QMessageBox::warning(this,"设置提醒","<font color='red'>当前设备没有可用的摄像头！</font>");
    }
    else{
        QString cameraname="";
        for(int i=0;i<cameras.size();i++)
        {
            cameraname=cameras[i].description();
            qDebug()<<cameraname;
            this->cameraBox->addItem(cameraname);
        }
    }

    this->videoPthBtn=new QPushButton("..",this);
    this->videoPthBtn->setObjectName("videoPthBtn");
    this->videoPthBtn->move(450,116);

    this->photoPthBtn=new QPushButton("..",this);
    this->photoPthBtn->setObjectName("photoPthBtn");
    this->photoPthBtn->move(450,176);
}

void SettingWin::loadQSS()
{
    QFile settingqss(":/qss/setting.qss");
    if(settingqss.open(QFile::ReadOnly))
    {
        qDebug()<<"Open Successfully!";//qDebug()函数：输出信息
        QString style=QLatin1String(settingqss.readAll());
        this->setStyleSheet(style);//为窗口设置样式
        settingqss.close();//打开文件后，要关闭文件
    }
    else
    {
        qDebug()<<"Open Failed!";
    }
}

void SettingWin::initConnect()
{
    connect(this->okBtn,SIGNAL(clicked()),this,SLOT(clickOK()));//点击确定按钮
    connect(this->videoPthBtn,SIGNAL(clicked()),this,SLOT(selectVideo()));//选择视频路径
    connect(this->photoPthBtn,SIGNAL(clicked()),this,SLOT(selectPhoto()));//选择照片路径
    connect(this->cancelBtn,SIGNAL(clicked()),this,SLOT(clickCancel()));//点击取消按钮
}

QList<QCameraInfo> SettingWin::getCameras() const
{
    return cameras;
}

void SettingWin::setCameras(const QList<QCameraInfo> &value)
{
    cameras = value;
}

void SettingWin::setVideoPth(QString path)
{
    this->videoPthEdt->setText(path);
}

void SettingWin::setPhotoPth(QString path)
{
    this->photoPthEdt->setText(path);
}

void SettingWin::setTimeBox(int index)
{
    this->timeBox->setCurrentIndex(index);
}

void SettingWin::setCameraBox(QString text)
{
    this->cameraBox->setCurrentText(text);
}

void SettingWin::clickOK()
{
    QString video_path="";
    QString photo_path="";
    int capture_interval=0;
    QString camera_name="";

    //表单是否为空的验证
    video_path=this->videoPthEdt->text();
    photo_path=this->photoPthEdt->text();
    capture_interval=this->timeBox->currentIndex()+1;
    camera_name=this->cameraBox->currentText();

    if(video_path.isEmpty())
    {
        qDebug()<<tr("未选择有效的视频路径");
        QMessageBox::critical(this,"设置提醒","<font color='red'>未选择有效的视频路径</font>");
        return;
    }
    else if (photo_path.isEmpty()) {
        QMessageBox::critical(this,"设置提醒","<font color='red'>未选择有效的图片路径</font>");
        qDebug()<<tr("未选择有效的图片路径");
        return;
    }
    emit setOK(video_path,photo_path,capture_interval,camera_name);//告诉开机界面，设置界面点击了确定，并携带设置信息
}

void SettingWin::selectVideo()
{
    QString videoPth=QFileDialog::getExistingDirectory(nullptr,tr("选择视频目录"),"../");
    if(!videoPth.isEmpty())
    {
        this->videoPthEdt->setText(videoPth);
    }
    else {
        QMessageBox::critical(this,tr("视频路径选择"),tr("<font color='red'>所选视频路径为空</font>"));
    }
}

void SettingWin::selectPhoto()
{
    /*getExistingDirectory()函数返回的是一个文件夹的绝对路径，如E:/2PROJECT/project2/data
     *参数1：父类指针，一般写作用 this表示本窗口类，控件一般都是窗口的子类，都继承自QWdiget
     *参数2：对话框的标题
     *参数3：默认打开的文件路径
    */
    QString photoPth=QFileDialog::getExistingDirectory(nullptr,tr("选择照片目录"),"../");
    if(!photoPth.isEmpty())
    {
        this->photoPthEdt->setText(photoPth);
    }
    else {
        QMessageBox::critical(this,tr("照片路径选择"),tr("<font color='red'>所选照片路径为空</font>"));
    }
}

void SettingWin::clickCancel()
{
    if(this->isfirst)
    {
        this->close();
    }
    else {
        emit settingCancel();
    }

}
