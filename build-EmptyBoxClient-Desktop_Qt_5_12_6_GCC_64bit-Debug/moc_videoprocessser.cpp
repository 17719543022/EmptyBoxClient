/****************************************************************************
** Meta object code from reading C++ file 'videoprocessser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EmptyBoxClient/Service/videoprocessser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoprocessser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoProcessSer_t {
    QByteArrayData data[14];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoProcessSer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoProcessSer_t qt_meta_stringdata_VideoProcessSer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VideoProcessSer"
QT_MOC_LITERAL(1, 16, 10), // "VideoFrame"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "camPort"
QT_MOC_LITERAL(4, 36, 10), // "frameIndex"
QT_MOC_LITERAL(5, 47, 4), // "data"
QT_MOC_LITERAL(6, 52, 3), // "len"
QT_MOC_LITERAL(7, 56, 6), // "nWidth"
QT_MOC_LITERAL(8, 63, 7), // "nHeight"
QT_MOC_LITERAL(9, 71, 17), // "VideoStatusResult"
QT_MOC_LITERAL(10, 89, 6), // "status"
QT_MOC_LITERAL(11, 96, 17), // "StartVideosignals"
QT_MOC_LITERAL(12, 114, 12), // "OnStartVideo"
QT_MOC_LITERAL(13, 127, 15) // "TestVideoOnline"

    },
    "VideoProcessSer\0VideoFrame\0\0camPort\0"
    "frameIndex\0data\0len\0nWidth\0nHeight\0"
    "VideoStatusResult\0status\0StartVideosignals\0"
    "OnStartVideo\0TestVideoOnline"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoProcessSer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,   39,    2, 0x06 /* Public */,
       9,    2,   52,    2, 0x06 /* Public */,
      11,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   58,    2, 0x08 /* Private */,
      13,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Long, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,   10,
    QMetaType::Int,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void,

       0        // eod
};

void VideoProcessSer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoProcessSer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->VideoFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 1: _t->VideoStatusResult((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: { int _r = _t->StartVideosignals();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->OnStartVideo();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->TestVideoOnline(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoProcessSer::*)(int , long , QByteArray , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoProcessSer::VideoFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VideoProcessSer::*)(const int & , const int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoProcessSer::VideoStatusResult)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = int (VideoProcessSer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoProcessSer::StartVideosignals)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoProcessSer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VideoProcessSer.data,
    qt_meta_data_VideoProcessSer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoProcessSer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoProcessSer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoProcessSer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VideoProcessSer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VideoProcessSer::VideoFrame(int _t1, long _t2, QByteArray _t3, int _t4, int _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoProcessSer::VideoStatusResult(const int & _t1, const int & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
int VideoProcessSer::StartVideosignals()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
