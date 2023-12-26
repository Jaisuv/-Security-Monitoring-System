#ifndef IMAGEPOPWIN_H
#define IMAGEPOPWIN_H

#include <QWidget>
#include <QRect>
#include <QListWidget>
#include <QLabel>

class imagePopWin : public QWidget
{
    Q_OBJECT
public:
    imagePopWin(QListWidgetItem *item,QRect rect,QWidget *parent = nullptr);
private:
    QLabel *lab;
protected:
    bool eventFilter(QObject *obj,QEvent *event);
signals:

public slots:
};

#endif // IMAGEPOPWIN_H
