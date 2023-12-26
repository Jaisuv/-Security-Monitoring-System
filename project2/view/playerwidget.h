#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QComboBox>
#include "thread/playh264.h"
#include <QCloseEvent>
#include "controller/photocontroller.h"
#include "controller/settingcontroller.h"
#include "controller/videocontroller.h"
#include "view/exportwidget.h"

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QString videoFile,int vId);
    void initCtrl();
    void loadQSS();
    void initConnect();
//    QString threadFile;
    PlayH264 *playH264Thread;
    ExportWidget *exportWidget;
private:
    QHBoxLayout *line1Layout,*line3Layout;
    QVBoxLayout *entireLayout,*middleLayout;
    QLabel *logoLab,*systemNameLab, //第一行，LOGO与名称
            *videoPlayLab;//视频显示
    QPushButton *previousBtn,*nextBtn,*swithBtn,*shotscreenBtn,*exportBtn;
    QSlider *processSlider;
    QComboBox *speedBox;
    QIcon icon1,icon2;
    bool isPlay;
    int videoId;
protected:
    void closeEvent(QCloseEvent *event);
signals:
//    void playstateChanged(bool);
    void successShotscreen();
public slots:
    void switchPlay();
    void receiveImg(QImage);
    void changeSpeed(int);
    void doShotScreen();
    void toPreVideo();
    void toNextVideo();
    void doExport();
};

#endif // PLAYERWIDGET_H
