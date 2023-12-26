/****************************************************************************
** Meta object code from reading C++ file 'replayh264.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../thread/replayh264.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'replayh264.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RePlayH264_t {
    QByteArrayData data[4];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RePlayH264_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RePlayH264_t qt_meta_stringdata_RePlayH264 = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RePlayH264"
QT_MOC_LITERAL(1, 11, 8), // "sendImg3"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10) // "playFinish"

    },
    "RePlayH264\0sendImg3\0\0playFinish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RePlayH264[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       3,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void,

       0        // eod
};

void RePlayH264::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RePlayH264 *_t = static_cast<RePlayH264 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendImg3((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->playFinish(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (RePlayH264::*_t)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RePlayH264::sendImg3)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RePlayH264::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RePlayH264::playFinish)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject RePlayH264::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_RePlayH264.data,
      qt_meta_data_RePlayH264,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RePlayH264::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RePlayH264::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RePlayH264.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int RePlayH264::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void RePlayH264::sendImg3(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RePlayH264::playFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
