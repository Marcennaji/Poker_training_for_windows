/****************************************************************************
** Meta object code from reading C++ file 'settingsdialogimpl.h'
**
** Created: Sat 12. Jan 12:36:57 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/settingsdialog/settingsdialogimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsdialogimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_settingsDialogImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      33,   19,   19,   19, 0x0a,
      53,   19,   19,   19, 0x0a,
      78,   19,   19,   19, 0x0a,
      95,   19,   19,   19, 0x0a,
     112,   19,   19,   19, 0x0a,
     129,   19,   19,   19, 0x0a,
     146,   19,   19,   19, 0x0a,
     163,   19,   19,   19, 0x0a,
     180,   19,   19,   19, 0x0a,
     197,   19,   19,   19, 0x0a,
     214,   19,   19,   19, 0x0a,
     231,   19,   19,   19, 0x0a,
     248,   19,   19,   19, 0x0a,
     278,   19,   19,   19, 0x0a,
     303,   19,   19,   19, 0x0a,
     330,   19,   19,   19, 0x0a,
     354,   19,   19,   19, 0x0a,
     391,   19,   19,   19, 0x0a,
     426,   19,   19,   19, 0x0a,
     446,   19,   19,   19, 0x0a,
     469,   19,   19,   19, 0x0a,
     505,   19,   19,   19, 0x0a,
     539,   19,   19,   19, 0x0a,
     558,   19,   19,   19, 0x0a,
     586,  580,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_settingsDialogImpl[] = {
    "settingsDialogImpl\0\0isAccepted()\0"
    "playerNickChanged()\0setFlipsidePicFileName()\0"
    "setAvatarFile0()\0setAvatarFile1()\0"
    "setAvatarFile2()\0setAvatarFile3()\0"
    "setAvatarFile4()\0setAvatarFile5()\0"
    "setAvatarFile6()\0setAvatarFile7()\0"
    "setAvatarFile8()\0setAvatarFile9()\0"
    "callManualBlindsOrderDialog()\0"
    "callSelectAvatarDialog()\0"
    "setFirstSmallBlindMargin()\0"
    "setLanguageChanged(int)\0"
    "setSelectedGameTableStyleActivated()\0"
    "showCurrentGameTableStylePreview()\0"
    "addGameTableStyle()\0removeGameTableStyle()\0"
    "setSelectedCardDeckStyleActivated()\0"
    "showCurrentCardDeckStylePreview()\0"
    "addCardDeckStyle()\0removeCardDeckStyle()\0"
    "event\0keyPressEvent(QKeyEvent*)\0"
};

void settingsDialogImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        settingsDialogImpl *_t = static_cast<settingsDialogImpl *>(_o);
        switch (_id) {
        case 0: _t->isAccepted(); break;
        case 1: _t->playerNickChanged(); break;
        case 2: _t->setFlipsidePicFileName(); break;
        case 3: _t->setAvatarFile0(); break;
        case 4: _t->setAvatarFile1(); break;
        case 5: _t->setAvatarFile2(); break;
        case 6: _t->setAvatarFile3(); break;
        case 7: _t->setAvatarFile4(); break;
        case 8: _t->setAvatarFile5(); break;
        case 9: _t->setAvatarFile6(); break;
        case 10: _t->setAvatarFile7(); break;
        case 11: _t->setAvatarFile8(); break;
        case 12: _t->setAvatarFile9(); break;
        case 13: _t->callManualBlindsOrderDialog(); break;
        case 14: _t->callSelectAvatarDialog(); break;
        case 15: _t->setFirstSmallBlindMargin(); break;
        case 16: _t->setLanguageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->setSelectedGameTableStyleActivated(); break;
        case 18: _t->showCurrentGameTableStylePreview(); break;
        case 19: _t->addGameTableStyle(); break;
        case 20: _t->removeGameTableStyle(); break;
        case 21: _t->setSelectedCardDeckStyleActivated(); break;
        case 22: _t->showCurrentCardDeckStylePreview(); break;
        case 23: _t->addCardDeckStyle(); break;
        case 24: _t->removeCardDeckStyle(); break;
        case 25: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData settingsDialogImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject settingsDialogImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_settingsDialogImpl,
      qt_meta_data_settingsDialogImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &settingsDialogImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *settingsDialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *settingsDialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_settingsDialogImpl))
        return static_cast<void*>(const_cast< settingsDialogImpl*>(this));
    if (!strcmp(_clname, "Ui::settingsDialog"))
        return static_cast< Ui::settingsDialog*>(const_cast< settingsDialogImpl*>(this));
    return QDialog::qt_metacast(_clname);
}

int settingsDialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
