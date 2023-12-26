#ifndef PLAYBACKWIDGET_OF_MAIN_H
#define PLAYBACKWIDGET_OF_MAIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QImage>
#include <QListWidget>
#include <QList>
#include <QStackedWidget>
#include "view/stackedWin/videoplaybackwidget.h"
#include "view/stackedWin/photoviewerwidget.h"

class PlaybackWidget_of_main : public QWidget
{
    Q_OBJECT
public:
    explicit PlaybackWidget_of_main(QWidget *parent = nullptr);
    void initCtrl();
    void loadQSS();
    void initConnect();
    QStackedWidget *rightWidget;
//    QWidget *photoViewerWidget;
    VideoPlaybackWidget *videoPlaybackWidget;
    PhotoViewerWidget *photoViewerWidget;
private:
    QHBoxLayout *entireLayout;
    QListWidget *leftGuide;
signals:

public slots:
    void refreshPhotoWall();
};

#endif // PLAYBACKWIDGET_OF_MAIN_H
