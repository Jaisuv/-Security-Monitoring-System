//日志界面
#ifndef LOGTABELWIDGET_H
#define LOGTABELWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QFont>
#include "controller/logcontroller.h"
#include "QHeaderView"
#include <QMessageBox>

class LogTabelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogTabelWidget(QWidget *parent = nullptr);
    void initUI();
    void initData();
private:
    QHBoxLayout *entireLayout;
    QVBoxLayout *leftLayout;
    QWidget *leftWidget;
    QLabel *Widgetab;
    QTableWidget *logTable;
    QStringList header;
    QList<MyLog *> logList;
signals:

public slots:
};

#endif // LOGTABELWIDGET_H
