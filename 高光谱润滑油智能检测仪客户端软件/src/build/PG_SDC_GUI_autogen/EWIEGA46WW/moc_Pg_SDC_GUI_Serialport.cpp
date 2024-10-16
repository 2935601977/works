/****************************************************************************
** Meta object code from reading C++ file 'Pg_SDC_GUI_Serialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/PgGUI/Pg_SDC_GUI_Serialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Pg_SDC_GUI_Serialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QSDCSerialPort_t {
    QByteArrayData data[21];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSDCSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSDCSerialPort_t qt_meta_stringdata_QSDCSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QSDCSerialPort"
QT_MOC_LITERAL(1, 15, 12), // "sigDataReady"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "sigWrite"
QT_MOC_LITERAL(4, 38, 11), // "const char*"
QT_MOC_LITERAL(5, 50, 9), // "sigSetCOM"
QT_MOC_LITERAL(6, 60, 8), // "sigClose"
QT_MOC_LITERAL(7, 69, 8), // "sigClear"
QT_MOC_LITERAL(8, 78, 8), // "sigFlush"
QT_MOC_LITERAL(9, 87, 13), // "slotDataReady"
QT_MOC_LITERAL(10, 101, 9), // "slotWrite"
QT_MOC_LITERAL(11, 111, 3), // "pch"
QT_MOC_LITERAL(12, 115, 10), // "slotSetCOM"
QT_MOC_LITERAL(13, 126, 6), // "strCOM"
QT_MOC_LITERAL(14, 133, 9), // "iBautRate"
QT_MOC_LITERAL(15, 143, 9), // "iDataBits"
QT_MOC_LITERAL(16, 153, 8), // "chParity"
QT_MOC_LITERAL(17, 162, 10), // "chStopBits"
QT_MOC_LITERAL(18, 173, 9), // "slotClose"
QT_MOC_LITERAL(19, 183, 9), // "slotClear"
QT_MOC_LITERAL(20, 193, 9) // "slotFlush"

    },
    "QSDCSerialPort\0sigDataReady\0\0sigWrite\0"
    "const char*\0sigSetCOM\0sigClose\0sigClear\0"
    "sigFlush\0slotDataReady\0slotWrite\0pch\0"
    "slotSetCOM\0strCOM\0iBautRate\0iDataBits\0"
    "chParity\0chStopBits\0slotClose\0slotClear\0"
    "slotFlush"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSDCSerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    2,   77,    2, 0x06 /* Public */,
       5,    5,   82,    2, 0x06 /* Public */,
       6,    0,   93,    2, 0x06 /* Public */,
       7,    0,   94,    2, 0x06 /* Public */,
       8,    0,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   96,    2, 0x08 /* Private */,
      10,    2,   97,    2, 0x08 /* Private */,
      12,    5,  102,    2, 0x08 /* Private */,
      18,    0,  113,    2, 0x08 /* Private */,
      19,    0,  114,    2, 0x08 /* Private */,
      20,    0,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, 0x80000000 | 4, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Char, QMetaType::Char,    2,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::LongLong,   11,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Char, QMetaType::Char,   13,   14,   15,   16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QSDCSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSDCSerialPort *_t = static_cast<QSDCSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigDataReady((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->sigWrite((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->sigSetCOM((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const char(*)>(_a[4])),(*reinterpret_cast< const char(*)>(_a[5]))); break;
        case 3: _t->sigClose(); break;
        case 4: _t->sigClear(); break;
        case 5: _t->sigFlush(); break;
        case 6: _t->slotDataReady(); break;
        case 7: _t->slotWrite((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 8: _t->slotSetCOM((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const char(*)>(_a[4])),(*reinterpret_cast< const char(*)>(_a[5]))); break;
        case 9: _t->slotClose(); break;
        case 10: _t->slotClear(); break;
        case 11: _t->slotFlush(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QSDCSerialPort::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSDCSerialPort::sigDataReady)) {
                *result = 0;
            }
        }
        {
            typedef void (QSDCSerialPort::*_t)(const char * , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSDCSerialPort::sigWrite)) {
                *result = 1;
            }
        }
        {
            typedef void (QSDCSerialPort::*_t)(const QString , const int , const int , const char , const char );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSDCSerialPort::sigSetCOM)) {
                *result = 2;
            }
        }
        {
            typedef void (QSDCSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSDCSerialPort::sigClose)) {
                *result = 3;
            }
        }
        {
            typedef void (QSDCSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSDCSerialPort::sigClear)) {
                *result = 4;
            }
        }
        {
            typedef void (QSDCSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSDCSerialPort::sigFlush)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject QSDCSerialPort::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSDCSerialPort.data,
      qt_meta_data_QSDCSerialPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QSDCSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSDCSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QSDCSerialPort.stringdata0))
        return static_cast<void*>(const_cast< QSDCSerialPort*>(this));
    return QObject::qt_metacast(_clname);
}

int QSDCSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void QSDCSerialPort::sigDataReady(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSDCSerialPort::sigWrite(const char * _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSDCSerialPort::sigSetCOM(const QString _t1, const int _t2, const int _t3, const char _t4, const char _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QSDCSerialPort::sigClose()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void QSDCSerialPort::sigClear()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void QSDCSerialPort::sigFlush()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
