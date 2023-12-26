#ifndef EXPORTWIDGET_H
#define EXPORTWIDGET_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCameraInfo>
#include <QList>
#include <QWidget>
#include <QFileDialog>
#include "thread/exportthread.h"
#include <QMessageBox>
#include <QString>

class ExportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExportWidget(QString fileH264);
    QString h264File;//把文件名传给线程
    void initCtrl();
private:
    QLabel *exPath,*exName,*exFormat;
    QLineEdit *pathEdt,*nameEdt;
    QComboBox *formatBox;
    QPushButton *pathBtn,*okBtn,*cancelBtn;
    ExportThread *exportThread;
signals:

public slots:
    void doSelect();
    void doOK();
    void doCancel();
    void taskDone();
};

#endif // EXPORTWIDGET_H
