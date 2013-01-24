/****************************************************************************
** Meta object code from reading C++ file 'changecompleteblindsdialogimpl.h'
**
** Created: Sat 12. Jan 12:36:46 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/changecompleteblindsdialog/changecompleteblindsdialogimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'changecompleteblindsdialogimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_changeCompleteBlindsDialogImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      37,   31,   32,   31, 0x0a,
      58,   31,   31,   31, 0x0a,
      89,   31,   31,   31, 0x0a,
     111,   31,   31,   31, 0x0a,
     133,   31,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_changeCompleteBlindsDialogImpl[] = {
    "changeCompleteBlindsDialogImpl\0\0bool\0"
    "getSettingsCorrect()\0"
    "updateSpinBoxInputMinimum(int)\0"
    "addBlindValueToList()\0removeBlindFromList()\0"
    "sortBlindsList()\0"
};

void changeCompleteBlindsDialogImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        changeCompleteBlindsDialogImpl *_t = static_cast<changeCompleteBlindsDialogImpl *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->getSettingsCorrect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: _t->updateSpinBoxInputMinimum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->addBlindValueToList(); break;
        case 3: _t->removeBlindFromList(); break;
        case 4: _t->sortBlindsList(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData changeCompleteBlindsDialogImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject changeCompleteBlindsDialogImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_changeCompleteBlindsDialogImpl,
      qt_meta_data_changeCompleteBlindsDialogImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &changeCompleteBlindsDialogImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *changeCompleteBlindsDialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *changeCompleteBlindsDialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_changeCompleteBlindsDialogImpl))
        return static_cast<void*>(const_cast< changeCompleteBlindsDialogImpl*>(this));
    if (!strcmp(_clname, "Ui::changeCompleteBlindsDialog"))
        return static_cast< Ui::changeCompleteBlindsDialog*>(const_cast< changeCompleteBlindsDialogImpl*>(this));
    return QDialog::qt_metacast(_clname);
}

int changeCompleteBlindsDialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
