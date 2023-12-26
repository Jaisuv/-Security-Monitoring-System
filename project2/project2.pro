#-------------------------------------------------
#
# Project created by QtCreator 2023-07-26T15:25:33
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
        view/myview.cpp \
        view/myitem.cpp \
    model/singleton_db.cpp \
    view/settingwin.cpp \
    view/loginwin.cpp \
    tools/verification.cpp \
    view/registwin.cpp \
    model/usermodel.cpp \
    controller/usercontroller.cpp \
    view/mainwin.cpp \
    model/settingmodel.cpp \
    controller/settingcontroller.cpp \
    view/stackedWin/monitorwidget_of_main.cpp \
    thread/cameraopenthread.cpp \
    tools/getmd5.cpp \
    thread/encode2h264.cpp \
    model/videomodel.cpp \
    controller/videocontroller.cpp \
    view/stackedWin/playbackwidget_of_main.cpp \
    tools/reboot.cpp \
    view/stackedWin/videoplaybackwidget.cpp \
    MyClass/myvideo.cpp \
    model/photomodel.cpp \
    controller/photocontroller.cpp \
    tools/mycalendarcombo.cpp \
    view/playerwidget.cpp \
    thread/playh264.cpp \
    view/stackedWin/photoviewerwidget.cpp \
    view/exportwidget.cpp \
    thread/exportthread.cpp \
    MyClass/myphoto.cpp \
    MyClass/imagepopwin.cpp \
    view/stackedWin/logtabelwidget.cpp \
    model/logmodel.cpp \
    controller/logcontroller.cpp \
    MyClass/mylog.cpp \
    thread/replayh264.cpp

HEADERS += \
        widget.h \
        view/myview.h \
        view/myitem.h \
    model/singleton_db.h \
    view/settingwin.h \
    view/loginwin.h \
    tools/verification.h \
    view/registwin.h \
    model/usermodel.h \
    controller/usercontroller.h \
    view/mainwin.h \
    model/settingmodel.h \
    controller/settingcontroller.h \
    view/stackedWin/monitorwidget_of_main.h \
    thread/cameraopenthread.h \
    tools/getmd5.h \
    thread/encode2h264.h \
    model/videomodel.h \
    controller/videocontroller.h \
    view/stackedWin/playbackwidget_of_main.h \
    tools/reboot.h \
    view/stackedWin/videoplaybackwidget.h \
    MyClass/myvideo.h \
    model/photomodel.h \
    controller/photocontroller.h \
    tools/mycalendarcombo.h \
    view/playerwidget.h \
    thread/playh264.h \
    view/stackedWin/photoviewerwidget.h \
    view/exportwidget.h \
    thread/exportthread.h \
    MyClass/myphoto.h \
    MyClass/imagepopwin.h \
    view/stackedWin/logtabelwidget.h \
    model/logmodel.h \
    controller/logcontroller.h \
    MyClass/mylog.h \
    thread/replayh264.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DESTDIR =bin
LIBS += $$PWD/lib/sqlite3.lib

INCLUDEPATH += ./ffmpeglib/include
LIBS += $$PWD/ffmpeglib/lib/avcodec.lib  \
        $$PWD/ffmpeglib/lib/avdevice.lib  \
        $$PWD/ffmpeglib/lib/avfilter.lib  \
        $$PWD/ffmpeglib/lib/avformat.lib  \
        $$PWD/ffmpeglib/lib/avutil.lib  \
        $$PWD/ffmpeglib/lib/swresample.lib  \
        $$PWD/ffmpeglib/lib/swscale.lib

RESOURCES += \
    resources.qrc
