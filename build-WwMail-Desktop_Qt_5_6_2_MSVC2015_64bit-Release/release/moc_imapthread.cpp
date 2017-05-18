/****************************************************************************
** Meta object code from reading C++ file 'imapthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WwMailV2.0/imapthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imapthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_imapThread_t {
    QByteArrayData data[10];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_imapThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_imapThread_t qt_meta_stringdata_imapThread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "imapThread"
QT_MOC_LITERAL(1, 11, 8), // "errorMsg"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "setimapAccount"
QT_MOC_LITERAL(4, 36, 12), // "AccountInfo*"
QT_MOC_LITERAL(5, 49, 12), // "imaperrorMsg"
QT_MOC_LITERAL(6, 62, 3), // "msg"
QT_MOC_LITERAL(7, 66, 10), // "imapstatus"
QT_MOC_LITERAL(8, 77, 6), // "status"
QT_MOC_LITERAL(9, 84, 10) // "setimapact"

    },
    "imapThread\0errorMsg\0\0setimapAccount\0"
    "AccountInfo*\0imaperrorMsg\0msg\0imapstatus\0"
    "status\0setimapact"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_imapThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       9,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,

       0        // eod
};

void imapThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        imapThread *_t = static_cast<imapThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->errorMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setimapAccount((*reinterpret_cast< AccountInfo*(*)>(_a[1]))); break;
        case 2: _t->imaperrorMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->imapstatus((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->setimapact(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (imapThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&imapThread::errorMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (imapThread::*_t)(AccountInfo * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&imapThread::setimapAccount)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject imapThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_imapThread.data,
      qt_meta_data_imapThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *imapThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *imapThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_imapThread.stringdata0))
        return static_cast<void*>(const_cast< imapThread*>(this));
    return QThread::qt_metacast(_clname);
}

int imapThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void imapThread::errorMsg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void imapThread::setimapAccount(AccountInfo * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_iMap_t {
    QByteArrayData data[25];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_iMap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_iMap_t qt_meta_stringdata_iMap = {
    {
QT_MOC_LITERAL(0, 0, 4), // "iMap"
QT_MOC_LITERAL(1, 5, 19), // "StartProgressDialog"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "SetProgress"
QT_MOC_LITERAL(4, 38, 19), // "CloseProgressDialog"
QT_MOC_LITERAL(5, 58, 8), // "errorMsg"
QT_MOC_LITERAL(6, 67, 10), // "warningMsg"
QT_MOC_LITERAL(7, 78, 13), // "changedstatus"
QT_MOC_LITERAL(8, 92, 17), // "addMailFolderlist"
QT_MOC_LITERAL(9, 110, 17), // "addMailHeaderlist"
QT_MOC_LITERAL(10, 128, 16), // "QList<MimeData>&"
QT_MOC_LITERAL(11, 145, 15), // "CreateEmlWindow"
QT_MOC_LITERAL(12, 161, 8), // "MimeData"
QT_MOC_LITERAL(13, 170, 11), // "const iMap*"
QT_MOC_LITERAL(14, 182, 12), // "startConnect"
QT_MOC_LITERAL(15, 195, 10), // "setAccount"
QT_MOC_LITERAL(16, 206, 18), // "const AccountInfo*"
QT_MOC_LITERAL(17, 225, 7), // "account"
QT_MOC_LITERAL(18, 233, 13), // "getHeaderList"
QT_MOC_LITERAL(19, 247, 11), // "useraccount"
QT_MOC_LITERAL(20, 259, 5), // "index"
QT_MOC_LITERAL(21, 265, 7), // "getBody"
QT_MOC_LITERAL(22, 273, 10), // "imapDelete"
QT_MOC_LITERAL(23, 284, 11), // "Folderindex"
QT_MOC_LITERAL(24, 296, 11) // "Headerindex"

    },
    "iMap\0StartProgressDialog\0\0SetProgress\0"
    "CloseProgressDialog\0errorMsg\0warningMsg\0"
    "changedstatus\0addMailFolderlist\0"
    "addMailHeaderlist\0QList<MimeData>&\0"
    "CreateEmlWindow\0MimeData\0const iMap*\0"
    "startConnect\0setAccount\0const AccountInfo*\0"
    "account\0getHeaderList\0useraccount\0"
    "index\0getBody\0imapDelete\0Folderindex\0"
    "Headerindex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_iMap[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    2,   85,    2, 0x06 /* Public */,
       4,    0,   90,    2, 0x06 /* Public */,
       5,    1,   91,    2, 0x06 /* Public */,
       6,    1,   94,    2, 0x06 /* Public */,
       7,    1,   97,    2, 0x06 /* Public */,
       8,    2,  100,    2, 0x06 /* Public */,
       9,    1,  105,    2, 0x06 /* Public */,
      11,    2,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  113,    2, 0x0a /* Public */,
      15,    1,  114,    2, 0x0a /* Public */,
      18,    2,  117,    2, 0x0a /* Public */,
      21,    2,  122,    2, 0x0a /* Public */,
      22,    2,  127,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    2,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 13,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   19,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   19,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   23,   24,

       0        // eod
};

void iMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        iMap *_t = static_cast<iMap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StartProgressDialog(); break;
        case 1: _t->SetProgress((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->CloseProgressDialog(); break;
        case 3: _t->errorMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->warningMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->changedstatus((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 6: _t->addMailFolderlist((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 7: _t->addMailHeaderlist((*reinterpret_cast< QList<MimeData>(*)>(_a[1]))); break;
        case 8: _t->CreateEmlWindow((*reinterpret_cast< const MimeData(*)>(_a[1])),(*reinterpret_cast< const iMap*(*)>(_a[2]))); break;
        case 9: _t->startConnect(); break;
        case 10: _t->setAccount((*reinterpret_cast< const AccountInfo*(*)>(_a[1]))); break;
        case 11: _t->getHeaderList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->getBody((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->imapDelete((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (iMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::StartProgressDialog)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (iMap::*_t)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::SetProgress)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (iMap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::CloseProgressDialog)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (iMap::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::errorMsg)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (iMap::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::warningMsg)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (iMap::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::changedstatus)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (iMap::*_t)(QString , QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::addMailFolderlist)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (iMap::*_t)(QList<MimeData> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::addMailHeaderlist)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (iMap::*_t)(const MimeData & , const iMap * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&iMap::CreateEmlWindow)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject iMap::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_iMap.data,
      qt_meta_data_iMap,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *iMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *iMap::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_iMap.stringdata0))
        return static_cast<void*>(const_cast< iMap*>(this));
    return QObject::qt_metacast(_clname);
}

int iMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void iMap::StartProgressDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void iMap::SetProgress(qint32 _t1, qint32 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void iMap::CloseProgressDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void iMap::errorMsg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void iMap::warningMsg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void iMap::changedstatus(qint32 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void iMap::addMailFolderlist(QString _t1, QStringList _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void iMap::addMailHeaderlist(QList<MimeData> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void iMap::CreateEmlWindow(const MimeData & _t1, const iMap * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
