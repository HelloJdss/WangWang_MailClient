/****************************************************************************
** Meta object code from reading C++ file 'emlbrower.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WwMailV2.0/emlbrower.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emlbrower.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_emlBrower_t {
    QByteArrayData data[17];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_emlBrower_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_emlBrower_t qt_meta_stringdata_emlBrower = {
    {
QT_MOC_LITERAL(0, 0, 9), // "emlBrower"
QT_MOC_LITERAL(1, 10, 10), // "deleteMail"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "reply"
QT_MOC_LITERAL(4, 28, 4), // "From"
QT_MOC_LITERAL(5, 33, 2), // "To"
QT_MOC_LITERAL(6, 36, 7), // "Subject"
QT_MOC_LITERAL(7, 44, 7), // "Content"
QT_MOC_LITERAL(8, 52, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(9, 74, 19), // "on_listView_clicked"
QT_MOC_LITERAL(10, 94, 5), // "index"
QT_MOC_LITERAL(11, 100, 25), // "on_listView_doubleClicked"
QT_MOC_LITERAL(12, 126, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(13, 150, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(14, 174, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(15, 198, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(16, 222, 23) // "on_pushButton_2_clicked"

    },
    "emlBrower\0deleteMail\0\0reply\0From\0To\0"
    "Subject\0Content\0on_pushButton_clicked\0"
    "on_listView_clicked\0index\0"
    "on_listView_doubleClicked\0"
    "on_pushButton_3_clicked\0on_pushButton_4_clicked\0"
    "on_pushButton_5_clicked\0on_pushButton_6_clicked\0"
    "on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_emlBrower[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       3,    4,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   78,    2, 0x08 /* Private */,
       9,    1,   79,    2, 0x08 /* Private */,
      11,    1,   82,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   10,
    QMetaType::Void, QMetaType::QModelIndex,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void emlBrower::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        emlBrower *_t = static_cast<emlBrower *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deleteMail((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 1: _t->reply((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_listView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_listView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_3_clicked(); break;
        case 6: _t->on_pushButton_4_clicked(); break;
        case 7: _t->on_pushButton_5_clicked(); break;
        case 8: _t->on_pushButton_6_clicked(); break;
        case 9: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (emlBrower::*_t)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&emlBrower::deleteMail)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (emlBrower::*_t)(const QString & , const QString & , const QString & , const QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&emlBrower::reply)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject emlBrower::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_emlBrower.data,
      qt_meta_data_emlBrower,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *emlBrower::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *emlBrower::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_emlBrower.stringdata0))
        return static_cast<void*>(const_cast< emlBrower*>(this));
    return QWidget::qt_metacast(_clname);
}

int emlBrower::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void emlBrower::deleteMail(qint32 _t1, qint32 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void emlBrower::reply(const QString & _t1, const QString & _t2, const QString & _t3, const QString _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
