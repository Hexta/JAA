/****************************************************************************
** Meta object code from reading C++ file 'face.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../GUI/Face/face.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'face.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Face[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      14,    5,    5,    5, 0x0a,
      38,    5,    5,    5, 0x0a,
      63,    5,    5,    5, 0x0a,
      74,    5,    5,    5, 0x0a,
      87,    5,    5,    5, 0x0a,
     133,  109,    5,    5, 0x0a,
     174,  109,    5,    5, 0x0a,
     217,  109,    5,    5, 0x0a,
     269,  254,    5,    5, 0x0a,
     322,  317,    5,    5, 0x0a,
     361,  317,    5,    5, 0x0a,
     429,  402,    5,    5, 0x0a,
     501,  485,    5,    5, 0x0a,
     529,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Face[] = {
    "Face\0\0about()\0selectFilesToCompress()\0"
    "selectFileToDecompress()\0compress()\0"
    "decompress()\0listArchiveContents()\0"
    "progress,fileName,speed\0"
    "displayCompressStatus(int,QString,float)\0"
    "displayDecompressStatus(int,QString,float)\0"
    "displayListStatus(int,QString,float)\0"
    "error,fileName\0"
    "showInfo(CTCompressorStatus::ErrorCode,QString)\0"
    "stat\0showCompressStatInfo(Compressor::Stat)\0"
    "showDecompressStatInfo(Compressor::Stat)\0"
    "blockSize,compressSequence\0"
    "setCompressSettings(uint,QList<Compressor::CoderTypes>)\0"
    "keepBrokenFiles\0setDecompressSettings(bool)\0"
    "initSettings()\0"
};

void Face::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Face *_t = static_cast<Face *>(_o);
        switch (_id) {
        case 0: _t->about(); break;
        case 1: _t->selectFilesToCompress(); break;
        case 2: _t->selectFileToDecompress(); break;
        case 3: _t->compress(); break;
        case 4: _t->decompress(); break;
        case 5: _t->listArchiveContents(); break;
        case 6: _t->displayCompressStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 7: _t->displayDecompressStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 8: _t->displayListStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 9: _t->showInfo((*reinterpret_cast< CTCompressorStatus::ErrorCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->showCompressStatInfo((*reinterpret_cast< Compressor::Stat(*)>(_a[1]))); break;
        case 11: _t->showDecompressStatInfo((*reinterpret_cast< Compressor::Stat(*)>(_a[1]))); break;
        case 12: _t->setCompressSettings((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QList<Compressor::CoderTypes>(*)>(_a[2]))); break;
        case 13: _t->setDecompressSettings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->initSettings(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Face::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Face::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Face,
      qt_meta_data_Face, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Face::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Face::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Face::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Face))
        return static_cast<void*>(const_cast< Face*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Face::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
