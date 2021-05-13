/****************************************************************************
** Meta object code from reading C++ file 'httpserverser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EmptyBoxClient/Service/httpserverser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpserverser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HttpServerSer_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HttpServerSer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HttpServerSer_t qt_meta_stringdata_HttpServerSer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "HttpServerSer"
QT_MOC_LITERAL(1, 14, 19), // "BoxRecoServerResult"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "BoxRecogResult"
QT_MOC_LITERAL(4, 50, 4), // "data"
QT_MOC_LITERAL(5, 55, 18), // "DeviceStatusResult"
QT_MOC_LITERAL(6, 74, 14), // "DevStatDisplay"
QT_MOC_LITERAL(7, 89, 3) // "dsd"

    },
    "HttpServerSer\0BoxRecoServerResult\0\0"
    "BoxRecogResult\0data\0DeviceStatusResult\0"
    "DevStatDisplay\0dsd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HttpServerSer[] = {

 // content:
       8,       // revision
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
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void HttpServerSer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HttpServerSer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BoxRecoServerResult((*reinterpret_cast< const BoxRecogResult(*)>(_a[1]))); break;
        case 1: _t->DeviceStatusResult((*reinterpret_cast< const DevStatDisplay(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BoxRecogResult >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HttpServerSer::*)(const BoxRecogResult & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpServerSer::BoxRecoServerResult)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HttpServerSer::*)(const DevStatDisplay & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpServerSer::DeviceStatusResult)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HttpServerSer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_HttpServerSer.data,
    qt_meta_data_HttpServerSer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HttpServerSer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HttpServerSer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HttpServerSer.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "RequstListener"))
        return static_cast< RequstListener*>(this);
    return QObject::qt_metacast(_clname);
}

int HttpServerSer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void HttpServerSer::BoxRecoServerResult(const BoxRecogResult & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HttpServerSer::DeviceStatusResult(const DevStatDisplay & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
