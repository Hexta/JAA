/****************************************************************************
** Meta object code from reading C++ file 'compressorThread.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../GUI/CompressorThread/compressorThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'compressorThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CompressorThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      42,   18,   17,   17, 0x05,
      95,   77,   17,   17, 0x05,
     149,  144,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     176,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CompressorThread[] = {
    "CompressorThread\0\0progress,fileName,speed\0"
    "progressChanged(int,QString,float)\0"
    "error,fileName,id\0"
    "info(CTCompressorStatus::ErrorCode,QString,uint)\0"
    "stat\0statInfo(Compressor::Stat)\0stop()\0"
};

void CompressorThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CompressorThread *_t = static_cast<CompressorThread *>(_o);
        switch (_id) {
        case 0: _t->progressChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 1: _t->info((*reinterpret_cast< CTCompressorStatus::ErrorCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 2: _t->statInfo((*reinterpret_cast< Compressor::Stat(*)>(_a[1]))); break;
        case 3: _t->stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CompressorThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CompressorThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CompressorThread,
      qt_meta_data_CompressorThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CompressorThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CompressorThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CompressorThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CompressorThread))
        return static_cast<void*>(const_cast< CompressorThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CompressorThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CompressorThread::progressChanged(int _t1, QString _t2, float _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CompressorThread::info(CTCompressorStatus::ErrorCode _t1, QString _t2, unsigned int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CompressorThread::statInfo(Compressor::Stat _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
