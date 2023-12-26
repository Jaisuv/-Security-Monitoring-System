/****************************************************************************
** Meta object code from reading C++ file 'playerwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/playerwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayerWidget_t {
    QByteArrayData data[10];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerWidget_t qt_meta_stringdata_PlayerWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PlayerWidget"
QT_MOC_LITERAL(1, 13, 17), // "successShotscreen"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 10), // "switchPlay"
QT_MOC_LITERAL(4, 43, 10), // "receiveImg"
QT_MOC_LITERAL(5, 54, 11), // "changeSpeed"
QT_MOC_LITERAL(6, 66, 12), // "doShotScreen"
QT_MOC_LITERAL(7, 79, 10), // "toPreVideo"
QT_MOC_LITERAL(8, 90, 11), // "toNextVideo"
QT_MOC_LITERAL(9, 102, 8) // "doExport"

    },
    "PlayerWidget\0successShotscreen\0\0"
    "switchPlay\0receiveImg\0changeSpeed\0"
    "doShotScreen\0toPreVideo\0toNextVideo\0"
    "doExport"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x0a /* Public */,
       4,    1,   56,    2, 0x0a /* Public */,
       5,    1,   59,    2, 0x0a /* Public */,
       6,    0,   62,    2, 0x0a /* Public */,
       7,    0,   63,    2, 0x0a /* Public */,
       8,    0,   64,    2, 0x0a /* Public */,
       9,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayerWidget *_t = static_cast<PlayerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->successShotscreen(); break;
        case 1: _t->switchPlay(); break;
        case 2: _t->receiveImg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 3: _t->changeSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->doShotScreen(); break;
        case 5: _t->toPreVideo(); break;
        case 6: _t->toNextVideo(); break;
        case 7: _t->doExport(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PlayerWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerWidget::successShotscreen)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PlayerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayerWidget.data,
      qt_meta_data_PlayerWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PlayerWidget::successShotscreen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
