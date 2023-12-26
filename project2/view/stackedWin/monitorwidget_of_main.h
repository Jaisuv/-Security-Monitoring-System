#ifndef MONITORWIDGET_OF_MAIN_H
#define MONITORWIDGET_OF_MAIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QImage>
//监控模式
#include "thread/cameraopenthread.h"
#include <QListWidget>
#include <QList>
#include <QCameraInfo>
#include "controller/settingcontroller.h"
#include "controller/photocontroller.h"
#include <QMovie>

class MonitorWidget_of_Main : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorWidget_of_Main(QWidget *parent = nullptr);
    void initCtrl();
    void loadQSS();
    void openCamera();
    QListWidget *getDevicesList() const;
    void setDevicesList(QListWidget *value);
    void initConnect();
    bool isLogin;
private:
    QWidget *deviceListWidget,*playBlockWidget,*fourChannelWidget,*channelSelectWidget;
    QHBoxLayout *totalLayout,*channelSelectLayout;
    QVBoxLayout *deviceListLayout,*playBlockLayout;
    QGridLayout *fourChannelLayout;
    QLabel *deviceTitle,*video1_label,*video2_label,*video3_label,*video4_label;
    QPushButton *channel1Btn,*channel2Btn,*channel3Btn,*channel4Btn,*fourChannelBtn,*screenshotBtn;
    CameraOpenThread *thread1;
    QListWidget *devicesList;
    QList<QCameraInfo> devices;
    QList<QLabel*> videoLabelList;
    int channelIndex;
signals:

public slots:
    void videoChannel1Show(QImage img);
    void screenshot();
    void toChannel1();
    void toChannel2();
    void toChannel3();
    void toChannel4();
    void form4Channel();
};

#endif // MONITORWIDGET_OF_MAIN_H
