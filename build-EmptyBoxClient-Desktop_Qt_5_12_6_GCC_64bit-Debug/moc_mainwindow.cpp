/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EmptyBoxClient/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 20), // "BoxTrackWorkerResult"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "BoxTrackData"
QT_MOC_LITERAL(4, 46, 4), // "data"
QT_MOC_LITERAL(5, 51, 20), // "OnDeviceStatusResult"
QT_MOC_LITERAL(6, 72, 14), // "DevStatDisplay"
QT_MOC_LITERAL(7, 87, 3), // "dsd"
QT_MOC_LITERAL(8, 91, 12), // "OnVideoFrame"
QT_MOC_LITERAL(9, 104, 5), // "image"
QT_MOC_LITERAL(10, 110, 5), // "camId"
QT_MOC_LITERAL(11, 116, 21), // "OnBoxRecoServerResult"
QT_MOC_LITERAL(12, 138, 14), // "BoxRecogResult"
QT_MOC_LITERAL(13, 153, 22), // "OnBoxTrackWorkerResult"
QT_MOC_LITERAL(14, 176, 20), // "on_ROISetBtn_clicked"
QT_MOC_LITERAL(15, 197, 24) // "on_ResultTxt_textChanged"

    },
    "MainWindow\0BoxTrackWorkerResult\0\0"
    "BoxTrackData\0data\0OnDeviceStatusResult\0"
    "DevStatDisplay\0dsd\0OnVideoFrame\0image\0"
    "camId\0OnBoxRecoServerResult\0BoxRecogResult\0"
    "OnBoxTrackWorkerResult\0on_ROISetBtn_clicked\0"
    "on_ResultTxt_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   52,    2, 0x08 /* Private */,
       8,    2,   55,    2, 0x08 /* Private */,
      11,    1,   60,    2, 0x08 /* Private */,
      13,    1,   63,    2, 0x08 /* Private */,
      14,    0,   66,    2, 0x08 /* Private */,
      15,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QImage, QMetaType::Int,    9,   10,
    QMetaType::Void, 0x80000000 | 12,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BoxTrackWorkerResult((*reinterpret_cast< const BoxTrackData(*)>(_a[1]))); break;
        case 1: _t->OnDeviceStatusResult((*reinterpret_cast< const DevStatDisplay(*)>(_a[1]))); break;
        case 2: _t->OnVideoFrame((*reinterpret_cast< const QImage(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->OnBoxRecoServerResult((*reinterpret_cast< const BoxRecogResult(*)>(_a[1]))); break;
        case 4: _t->OnBoxTrackWorkerResult((*reinterpret_cast< const BoxTrackData(*)>(_a[1]))); break;
        case 5: _t->on_ROISetBtn_clicked(); break;
        case 6: _t->on_ResultTxt_textChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BoxTrackData >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BoxRecogResult >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BoxTrackData >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const BoxTrackData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::BoxTrackWorkerResult)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::BoxTrackWorkerResult(const BoxTrackData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
