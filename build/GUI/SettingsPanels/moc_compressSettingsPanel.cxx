/****************************************************************************
** Meta object code from reading C++ file 'compressSettingsPanel.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../GUI/SettingsPanels/compressSettingsPanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'compressSettingsPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CompressSettingsPanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      50,   23,   22,   22, 0x05,
     102,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     120,   23,   22,   22, 0x0a,
     160,   22,   22,   22, 0x08,
     166,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CompressSettingsPanel[] = {
    "CompressSettingsPanel\0\0"
    "blockSize,compressSequence\0"
    "settingsChanged(uint,QList<Compressor::CoderTypes>)\0"
    "resetToDefaults()\0"
    "set(uint,QList<Compressor::CoderTypes>)\0"
    "get()\0disableEncoders()\0"
};

void CompressSettingsPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CompressSettingsPanel *_t = static_cast<CompressSettingsPanel *>(_o);
        switch (_id) {
        case 0: _t->settingsChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QList<Compressor::CoderTypes>(*)>(_a[2]))); break;
        case 1: _t->resetToDefaults(); break;
        case 2: _t->set((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QList<Compressor::CoderTypes>(*)>(_a[2]))); break;
        case 3: _t->get(); break;
        case 4: _t->disableEncoders(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CompressSettingsPanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CompressSettingsPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CompressSettingsPanel,
      qt_meta_data_CompressSettingsPanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CompressSettingsPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CompressSettingsPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CompressSettingsPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CompressSettingsPanel))
        return static_cast<void*>(const_cast< CompressSettingsPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int CompressSettingsPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CompressSettingsPanel::settingsChanged(unsigned int _t1, QList<Compressor::CoderTypes> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CompressSettingsPanel::resetToDefaults()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
