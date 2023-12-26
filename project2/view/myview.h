#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>    //视图类
#include <QGraphicsScene>   //场景
#include "myitem.h"
#include <QTimer>   //定时器
#include <QThread>
#include "view/settingwin.h"
#include "view/mainwin.h"
#include "controller/settingcontroller.h"
#include <QList>
#include <QCameraInfo>
#include "tools/reboot.h"

class MyView:public QGraphicsView
{
    Q_OBJECT
public:
    MyView();
    ~MyView();
private:
    QGraphicsScene *myScene;    //场景
    MyItem *item1,*item2;       //图元
    QTimer *timer;              //定时器
    SettingWin *settingWin;
    MainWin *mainWin;
    QList<QCameraInfo> cameras;
signals:

public slots:
    void stopMove();
    void toMainWin(QString,QString,int,QString);
    void showSetting();
    void setC2Main();
};

#endif // MYVIEW_H
