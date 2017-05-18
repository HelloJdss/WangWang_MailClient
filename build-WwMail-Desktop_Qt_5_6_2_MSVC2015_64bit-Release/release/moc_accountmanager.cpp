/****************************************************************************
** Meta object code from reading C++ file 'accountmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WwMailV2.0/accountmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accountmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AccountManager_t {
    QByteArrayData data[18];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AccountManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AccountManager_t qt_meta_stringdata_AccountManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AccountManager"
QT_MOC_LITERAL(1, 15, 13), // "clearcomboBox"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "additemcomboBox"
QT_MOC_LITERAL(4, 46, 16), // "createimapThread"
QT_MOC_LITERAL(5, 63, 11), // "AccountInfo"
QT_MOC_LITERAL(6, 75, 16), // "updateimapThread"
QT_MOC_LITERAL(7, 92, 17), // "destroyimapThread"
QT_MOC_LITERAL(8, 110, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(9, 132, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(10, 164, 5), // "index"
QT_MOC_LITERAL(11, 170, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(12, 194, 10), // "addaccount"
QT_MOC_LITERAL(13, 205, 8), // "username"
QT_MOC_LITERAL(14, 214, 12), // "userpassword"
QT_MOC_LITERAL(15, 227, 13), // "updateManager"
QT_MOC_LITERAL(16, 241, 11), // "editaccount"
QT_MOC_LITERAL(17, 253, 12) // "saveaccounts"

    },
    "AccountManager\0clearcomboBox\0\0"
    "additemcomboBox\0createimapThread\0"
    "AccountInfo\0updateimapThread\0"
    "destroyimapThread\0on_pushButton_clicked\0"
    "on_comboBox_currentIndexChanged\0index\0"
    "on_pushButton_3_clicked\0addaccount\0"
    "username\0userpassword\0updateManager\0"
    "editaccount\0saveaccounts"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AccountManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       4,    1,   78,    2, 0x06 /* Public */,
       6,    1,   81,    2, 0x06 /* Public */,
       7,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   87,    2, 0x08 /* Private */,
       9,    1,   88,    2, 0x08 /* Private */,
      11,    0,   91,    2, 0x08 /* Private */,
      12,    2,   92,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,
      16,    1,   98,    2, 0x0a /* Public */,
      17,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void AccountManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AccountManager *_t = static_cast<AccountManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearcomboBox(); break;
        case 1: _t->additemcomboBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->createimapThread((*reinterpret_cast< AccountInfo(*)>(_a[1]))); break;
        case 3: _t->updateimapThread((*reinterpret_cast< AccountInfo(*)>(_a[1]))); break;
        case 4: _t->destroyimapThread((*reinterpret_cast< AccountInfo(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_clicked(); break;
        case 6: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_3_clicked(); break;
        case 8: _t->addaccount((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->updateManager(); break;
        case 10: _t->editaccount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->saveaccounts(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AccountManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountManager::clearcomboBox)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AccountManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountManager::additemcomboBox)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AccountManager::*_t)(AccountInfo );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountManager::createimapThread)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AccountManager::*_t)(AccountInfo );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountManager::updateimapThread)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AccountManager::*_t)(AccountInfo );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AccountManager::destroyimapThread)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject AccountManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AccountManager.data,
      qt_meta_data_AccountManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AccountManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AccountManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AccountManager.stringdata0))
        return static_cast<void*>(const_cast< AccountManager*>(this));
    return QWidget::qt_metacast(_clname);
}

int AccountManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void AccountManager::clearcomboBox()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void AccountManager::additemcomboBox(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AccountManager::createimapThread(AccountInfo _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AccountManager::updateimapThread(AccountInfo _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AccountManager::destroyimapThread(AccountInfo _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
