/****************************************************************************
** Meta object code from reading C++ file 'selectavatardialogimpl.h'
**
** Created: Sat 12. Jan 12:37:02 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/settingsdialog/selectavatardialog/selectavatardialogimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectavatardialogimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_selectAvatarDialogImpl[] = {

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
      24,   23,   23,   23, 0x0a,
      46,   23,   23,   23, 0x0a,
      68,   23,   23,   23, 0x0a,
      81,   23,   23,   23, 0x0a,
     102,   23,   94,   23, 0x0a,
     118,   23,   23,   23, 0x0a,
     143,   23,  138,   23, 0x0a,
     164,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_selectAvatarDialogImpl[] = {
    "selectAvatarDialogImpl\0\0toggleGroupBox1(bool)\0"
    "toggleGroupBox2(bool)\0isAccepted()\0"
    "isRejected()\0QString\0getAvatarLink()\0"
    "setExternalAvatar()\0bool\0getSettingsCorrect()\0"
    "refreshAvatarView()\0"
};

void selectAvatarDialogImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        selectAvatarDialogImpl *_t = static_cast<selectAvatarDialogImpl *>(_o);
        switch (_id) {
        case 0: _t->toggleGroupBox1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->toggleGroupBox2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->isAccepted(); break;
        case 3: _t->isRejected(); break;
        case 4: { QString _r = _t->getAvatarLink();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: _t->setExternalAvatar(); break;
        case 6: { bool _r = _t->getSettingsCorrect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->refreshAvatarView(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData selectAvatarDialogImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject selectAvatarDialogImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_selectAvatarDialogImpl,
      qt_meta_data_selectAvatarDialogImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &selectAvatarDialogImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *selectAvatarDialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *selectAvatarDialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_selectAvatarDialogImpl))
        return static_cast<void*>(const_cast< selectAvatarDialogImpl*>(this));
    if (!strcmp(_clname, "Ui::selectAvatarDialog"))
        return static_cast< Ui::selectAvatarDialog*>(const_cast< selectAvatarDialogImpl*>(this));
    return QDialog::qt_metacast(_clname);
}

int selectAvatarDialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
