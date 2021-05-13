/****************************************************************************
** Meta object code from reading C++ file 'detectemptyboxser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EmptyBoxClient/Service/detectemptyboxser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'detectemptyboxser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DetectEmptyBoxSer_t {
    QByteArrayData data[17];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DetectEmptyBoxSer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DetectEmptyBoxSer_t qt_meta_stringdata_DetectEmptyBoxSer = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DetectEmptyBoxSer"
QT_MOC_LITERAL(1, 18, 10), // "VideoFrame"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "image"
QT_MOC_LITERAL(4, 36, 5), // "camId"
QT_MOC_LITERAL(5, 42, 18), // "DeviceStatusResult"
QT_MOC_LITERAL(6, 61, 14), // "DevStatDisplay"
QT_MOC_LITERAL(7, 76, 3), // "dsd"
QT_MOC_LITERAL(8, 80, 12), // "OnVideoFrame"
QT_MOC_LITERAL(9, 93, 7), // "camPort"
QT_MOC_LITERAL(10, 101, 8), // "frmIndex"
QT_MOC_LITERAL(11, 110, 8), // "bImgData"
QT_MOC_LITERAL(12, 119, 7), // "nImgLen"
QT_MOC_LITERAL(13, 127, 6), // "nWidth"
QT_MOC_LITERAL(14, 134, 7), // "nHeight"
QT_MOC_LITERAL(15, 142, 19), // "OnVideoStatusResult"
QT_MOC_LITERAL(16, 162, 6) // "status"

    },
    "DetectEmptyBoxSer\0VideoFrame\0\0image\0"
    "camId\0DeviceStatusResult\0DevStatDisplay\0"
    "dsd\0OnVideoFrame\0camPort\0frmIndex\0"
    "bImgData\0nImgLen\0nWidth\0nHeight\0"
    "OnVideoStatusResult\0status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DetectEmptyBoxSer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    6,   42,    2, 0x08 /* Private */,
      15,    2,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage, QMetaType::Int,    3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   16,

       0        // eod
};

void DetectEmptyBoxSer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DetectEmptyBoxSer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->VideoFrame((*reinterpret_cast< const QImage(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: _t->DeviceStatusResult((*reinterpret_cast< const DevStatDisplay(*)>(_a[1]))); break;
        case 2: _t->OnVideoFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 3: _t->OnVideoStatusResult((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DetectEmptyBoxSer::*)(const QImage & , const int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DetectEmptyBoxSer::VideoFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DetectEmptyBoxSer::*)(const DevStatDisplay & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DetectEmptyBoxSer::DeviceStatusResult)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DetectEmptyBoxSer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DetectEmptyBoxSer.data,
    qt_meta_data_DetectEmptyBoxSer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DetectEmptyBoxSer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DetectEmptyBoxSer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DetectEmptyBoxSer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DetectEmptyBoxSer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DetectEmptyBoxSer::VideoFrame(const QImage & _t1, const int & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DetectEmptyBoxSer::DeviceStatusResult(const DevStatDisplay & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
