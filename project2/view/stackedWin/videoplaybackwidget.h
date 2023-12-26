#ifndef VIDEOPLAYBACKWIDGET_H
#define VIDEOPLAYBACKWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include "controller/videocontroller.h"
#include <QList>
#include <QCalendarWidget>
#include <QDateEdit>
#include "view/playerwidget.h"
#include <QTimer>
#include "thread/playh264.h"
#include "thread/replayh264.h"

class VideoPlaybackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlaybackWidget(QWidget *parent = nullptr);
    void initCtrl();
    void initData();
    void initConnect();
    void playPrepare();
private:
    QHBoxLayout *entireLayout,*buttonLayout,*searchLayout;
    QVBoxLayout *rightLayout,*leftLayout;
    QWidget *leftWidget,*rightWidget;
    QLabel *latestVideo,*pageLab,
           *searchNote;
    QPushButton *PgUp,*PgDn;//查询按钮，上一页按钮，下一页按钮
    QPushButton *PgUp2,*PgDn2;//
    QListWidget *videoListWiget;
    QList<MyVideo *> videoList;
    int currentPage,totalPage;
    bool calendarisOpen;
    QDateEdit *dateEdt;
    PlayerWidget *playWin;
    int videoId;
    RePlayH264 *replayH264;
signals:
    void playerDoScreenShot();
public slots:
    void PageUp();
    void PageDown();
    void PlaybackVideo(QListWidgetItem *);
    void refreshList(QDate);
    void getImage(QImage);
    void restartVideo();
};

#endif // VIDEOPLAYBACKWIDGET_H
