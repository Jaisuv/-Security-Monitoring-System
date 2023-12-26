#include "widget.h"
#include <QApplication>
#include "view/myview.h"
#include "view/stackedWin/monitorwidget_of_main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    MyView mv;
    mv.show();

//    MonitorWidget_of_Main monitor;
//    monitor.show();

    return a.exec();
}
