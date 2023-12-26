/****************************************************************************
** Meta object code from reading C++ file 'videoplaybackwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/stackedWin/videoplaybackwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoplaybackwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoPlaybackWidget_t {
    QByteArrayData data[10];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoPlaybackWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoPlaybackWidget_t qt_meta_stringdata_VideoPlaybackWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "VideoPlaybackWidget"
QT_MOC_LITERAL(1, 20, 18), // "playerDoScreenShot"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 6), // "PageUp"
QT_MOC_LITERAL(4, 47, 8), // "PageDown"
QT_MOC_LITERAL(5, 56, 13), // "PlaybackVideo"
QT_MOC_LITERAL(6, 70, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 87, 11), // "refreshList"
QT_MOC_LITERAL(8, 99, 8), // "getImage"
QT_MOC_LITERAL(9, 108, 12) // "restartVideo"

    },
    "VideoPlaybackWidget\0playerDoScreenShot\0"
    "\0PageUp\0PageDown\0PlaybackVideo\0"
    "QListWidgetItem*\0refreshList\0getImage\0"
    "restartVideo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoPlaybackWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    1,   52,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,
       8,    1,   58,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::QDate,    2,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void,

       0        // eod
};

void VideoPlaybackWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoPlaybackWidget *_t = static_cast<VideoPlaybackWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playerDoScreenShot(); break;
        case 1: _t->PageUp(); break;
        case 2: _t->PageDown(); break;
        case 3: _t->PlaybackVideo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->refreshList((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 5: _t->getImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 6: _t->restartVideo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (VideoPlaybackWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoPlaybackWidget::playerDoScreenShot)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject VideoPlaybackWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoPlaybackWidget.data,
      qt_meta_data_VideoPlaybackWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VideoPlaybackWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPlaybackWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPlaybackWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VideoPlaybackWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void VideoPlaybackWidget::playerDoScreenShot()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
