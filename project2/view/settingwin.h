#ifndef SETTINGWIN_H
#define SETTINGWIN_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCameraInfo>
#include <QList>
#include <QWidget>
#include "controller/settingcontroller.h"

class SettingWin : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWin(QWidget *parent = nullptr);
    void initCtrl();
    void loadQSS();
    void initConnect();
    QList<QCameraInfo> getCameras() const;
    void setCameras(const QList<QCameraInfo> &value);
    void setVideoPth(QString path);
    void setPhotoPth(QString path);
    bool isfirst;
    void setTimeBox(int index);
    void setCameraBox(QString text);
private:
    QLabel *title,*videoPthLab,*photoPthLab,*time_interval,*camera_setting;
    QLineEdit *videoPthEdt,*photoPthEdt;
    QComboBox *timeBox,*cameraBox;
    QPushButton *okBtn,*cancelBtn,*videoPthBtn,*photoPthBtn;
    QList<QCameraInfo> cameras;
signals:
    void setOK(QString,QString,int,QString);
    void settingCancel();
public slots:
    void clickOK();
    void selectVideo();
    void selectPhoto();
    void clickCancel();
};

#endif // SETTINGWIN_H
