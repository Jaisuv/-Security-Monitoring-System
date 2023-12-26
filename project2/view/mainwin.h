#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimerEvent>
#include <QList>
#include <QCameraInfo>
#include <QListWidget>
#include <QListWidgetItem>
#include "controller/usercontroller.h"
//模式切换界面
#include "view/loginwin.h"
#include "view/stackedWin/monitorwidget_of_main.h"
#include "view/stackedWin/playbackwidget_of_main.h"
#include "view/stackedWin/logtabelwidget.h"
#include "controller/videocontroller.h"

class MainWin : public QWidget
{
    Q_OBJECT
public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();
    void initUi();
    void initConnect();
    void loadQSS();
    //监控直播画面
    MonitorWidget_of_Main *monitorWidget;
    //回放与照片模式
    PlaybackWidget_of_main *playbackWidget;
    //系统日志模式
    LogTabelWidget *logTablUI;
    QPushButton *getLogoutBtn() const;
    void setLogoutBtn(QPushButton *value);

private:
    //logo 安防监控系统  时间
    QLabel *logoLab,*titleLab,*timeLab;
    //视频监控  视频回放 系统日志 系统设置  登录 退出
    QPushButton *monitorBtn,*playbackBtn,*logBtn,*settingBtn,*loginBtn,*logoutBtn;
    //导航栏
    QWidget *guideWidget;
    //整体布局
    QVBoxLayout *mainlayout;
    //模式切换的堆栈窗
    QStackedWidget *widgetStack;
    //导航栏的水平布局
    QHBoxLayout *guideLayout;
    //登录窗口
    LoginWin *SigninWidget;
protected:
    void timerEvent(QTimerEvent *event);
signals:
    void toSetting();
public slots:
    void showMonitor();
    void showPlayback();
    void showLog();
    void showSignIn();
    void LoginSuccess(QString name);
    void Logout();
};

#endif // MAINWIN_H
