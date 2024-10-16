/****************************************************************************
** Meta object code from reading C++ file 'Pg_SDC_GUI_EntryWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/PgGUI/PgDM/Pg_SDC_GUI_EntryWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Pg_SDC_GUI_EntryWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EntryWidget_t {
    QByteArrayData data[13];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EntryWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EntryWidget_t qt_meta_stringdata_EntryWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "EntryWidget"
QT_MOC_LITERAL(1, 12, 18), // "downFrameRequested"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 12), // "EntryWidget*"
QT_MOC_LITERAL(4, 45, 11), // "entryWidget"
QT_MOC_LITERAL(5, 57, 13), // "showDownFrame"
QT_MOC_LITERAL(6, 71, 16), // "ParameterDisplay"
QT_MOC_LITERAL(7, 88, 12), // "CurveDisplay"
QT_MOC_LITERAL(8, 101, 30), // "SampleCollectionDetailsDisplay"
QT_MOC_LITERAL(9, 132, 30), // "ElementDetectionDetailsDisplay"
QT_MOC_LITERAL(10, 163, 8), // "showItem"
QT_MOC_LITERAL(11, 172, 8), // "itemInfo"
QT_MOC_LITERAL(12, 181, 2) // "on"

    },
    "EntryWidget\0downFrameRequested\0\0"
    "EntryWidget*\0entryWidget\0showDownFrame\0"
    "ParameterDisplay\0CurveDisplay\0"
    "SampleCollectionDetailsDisplay\0"
    "ElementDetectionDetailsDisplay\0showItem\0"
    "itemInfo\0on"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EntryWidget[] = {

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
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,
       9,    0,   56,    2, 0x08 /* Private */,
      10,    2,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant, QMetaType::Bool,   11,   12,

       0        // eod
};

void EntryWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EntryWidget *_t = static_cast<EntryWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downFrameRequested((*reinterpret_cast< EntryWidget*(*)>(_a[1]))); break;
        case 1: _t->showDownFrame(); break;
        case 2: _t->ParameterDisplay(); break;
        case 3: _t->CurveDisplay(); break;
        case 4: _t->SampleCollectionDetailsDisplay(); break;
        case 5: _t->ElementDetectionDetailsDisplay(); break;
        case 6: _t->showItem((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< EntryWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EntryWidget::*_t)(EntryWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EntryWidget::downFrameRequested)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject EntryWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EntryWidget.data,
      qt_meta_data_EntryWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EntryWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EntryWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EntryWidget.stringdata0))
        return static_cast<void*>(const_cast< EntryWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int EntryWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void EntryWidget::downFrameRequested(EntryWidget * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
