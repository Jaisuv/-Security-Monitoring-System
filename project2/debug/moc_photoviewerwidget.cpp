/****************************************************************************
** Meta object code from reading C++ file 'photoviewerwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view/stackedWin/photoviewerwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'photoviewerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PhotoViewerWidget_t {
    QByteArrayData data[6];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PhotoViewerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PhotoViewerWidget_t qt_meta_stringdata_PhotoViewerWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "PhotoViewerWidget"
QT_MOC_LITERAL(1, 18, 13), // "showPhotoInfo"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 50, 10), // "enlargeImg"
QT_MOC_LITERAL(5, 61, 10) // "initByDate"

    },
    "PhotoViewerWidget\0showPhotoInfo\0\0"
    "QListWidgetItem*\0enlargeImg\0initByDate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PhotoViewerWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QDate,    2,

       0        // eod
};

void PhotoViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PhotoViewerWidget *_t = static_cast<PhotoViewerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showPhotoInfo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->enlargeImg((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->initByDate((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PhotoViewerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PhotoViewerWidget.data,
      qt_meta_data_PhotoViewerWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PhotoViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PhotoViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PhotoViewerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PhotoViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
