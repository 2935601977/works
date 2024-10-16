/****************************************************************************
** Meta object code from reading C++ file 'Pg_SDC_GUI_SystemSettingTipsWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/PgGUI/PgSS/Pg_SDC_GUI_SystemSettingTipsWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Pg_SDC_GUI_SystemSettingTipsWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QSystemSettTipsWidget_t {
    QByteArrayData data[8];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSystemSettTipsWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSystemSettTipsWidget_t qt_meta_stringdata_QSystemSettTipsWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "QSystemSettTipsWidget"
QT_MOC_LITERAL(1, 22, 8), // "showItem"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "itemInfo"
QT_MOC_LITERAL(4, 41, 2), // "on"
QT_MOC_LITERAL(5, 44, 13), // "slotItemEnter"
QT_MOC_LITERAL(6, 58, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(7, 76, 4) // "item"

    },
    "QSystemSettTipsWidget\0showItem\0\0"
    "itemInfo\0on\0slotItemEnter\0QTableWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSystemSettTipsWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x0a /* Public */,
       5,    1,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariant, QMetaType::Bool,    3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void QSystemSettTipsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSystemSettTipsWidget *_t = static_cast<QSystemSettTipsWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showItem((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->slotItemEnter((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QSystemSettTipsWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSystemSettTipsWidget.data,
      qt_meta_data_QSystemSettTipsWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QSystemSettTipsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSystemSettTipsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QSystemSettTipsWidget.stringdata0))
        return static_cast<void*>(const_cast< QSystemSettTipsWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSystemSettTipsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
