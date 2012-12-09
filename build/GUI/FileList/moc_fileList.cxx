/****************************************************************************
** Meta object code from reading C++ file 'fileList.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../GUI/FileList/fileList.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fileList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileList[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      29,   17,    9,    9, 0x0a,
      64,   17,    9,    9, 0x0a,
      96,   17,    9,    9, 0x0a,
     131,   17,    9,    9, 0x0a,
     169,   17,    9,    9, 0x0a,
     206,   17,    9,    9, 0x0a,
     263,  245,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FileList[] = {
    "FileList\0\0init()\0fileName,id\0"
    "setProceedFileStatus(QString,uint)\0"
    "setFailFileStatus(QString,uint)\0"
    "setSuccessFileStatus(QString,uint)\0"
    "setCancelledFilesStatus(QString,uint)\0"
    "setCorruptedFileStatus(QString,uint)\0"
    "setUnCorruptedFileStatus(QString,uint)\0"
    "error,fileName,id\0"
    "showInfo(CTCompressorStatus::ErrorCode,QString,uint)\0"
};

void FileList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileList *_t = static_cast<FileList *>(_o);
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->setProceedFileStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 2: _t->setFailFileStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->setSuccessFileStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 4: _t->setCancelledFilesStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 5: _t->setCorruptedFileStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 6: _t->setUnCorruptedFileStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 7: _t->showInfo((*reinterpret_cast< CTCompressorStatus::ErrorCode(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileList::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileList::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_FileList,
      qt_meta_data_FileList, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileList))
        return static_cast<void*>(const_cast< FileList*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int FileList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
