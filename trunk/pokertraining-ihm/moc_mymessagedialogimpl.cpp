/****************************************************************************
** Meta object code from reading C++ file 'mymessagedialogimpl.h'
**
** Created: Sat 12. Jan 12:36:55 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/mymessagedialog/mymessagedialogimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mymessagedialogimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myMessageDialogImpl[] = {

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
      29,   26,   21,   20, 0x0a,
     114,   69,   65,   20, 0x0a,
     219,  187,   65,   20, 0x2a,
     287,   69,   20,   20, 0x0a,
     360,  187,   20,   20, 0x2a,
     428,   20,   20,   20, 0x0a,
     437,   20,   20,   20, 0x0a,
     446,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myMessageDialogImpl[] = {
    "myMessageDialogImpl\0\0bool\0id\0"
    "checkIfMesssageWillBeDisplayed(int)\0"
    "int\0messageId,msg,title,pix,buttons,showCheckBox\0"
    "exec(int,QString,QString,QPixmap,QDialogButtonBox::StandardButtons,boo"
    "l)\0"
    "messageId,msg,title,pix,buttons\0"
    "exec(int,QString,QString,QPixmap,QDialogButtonBox::StandardButtons)\0"
    "show(int,QString,QString,QPixmap,QDialogButtonBox::StandardButtons,boo"
    "l)\0"
    "show(int,QString,QString,QPixmap,QDialogButtonBox::StandardButtons)\0"
    "accept()\0reject()\0writeConfig()\0"
};

void myMessageDialogImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        myMessageDialogImpl *_t = static_cast<myMessageDialogImpl *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->checkIfMesssageWillBeDisplayed((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->exec((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QPixmap(*)>(_a[4])),(*reinterpret_cast< QDialogButtonBox::StandardButtons(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->exec((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QPixmap(*)>(_a[4])),(*reinterpret_cast< QDialogButtonBox::StandardButtons(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: _t->show((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QPixmap(*)>(_a[4])),(*reinterpret_cast< QDialogButtonBox::StandardButtons(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 4: _t->show((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QPixmap(*)>(_a[4])),(*reinterpret_cast< QDialogButtonBox::StandardButtons(*)>(_a[5]))); break;
        case 5: _t->accept(); break;
        case 6: _t->reject(); break;
        case 7: _t->writeConfig(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData myMessageDialogImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject myMessageDialogImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_myMessageDialogImpl,
      qt_meta_data_myMessageDialogImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myMessageDialogImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myMessageDialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myMessageDialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myMessageDialogImpl))
        return static_cast<void*>(const_cast< myMessageDialogImpl*>(this));
    if (!strcmp(_clname, "Ui::myMessageDialog"))
        return static_cast< Ui::myMessageDialog*>(const_cast< myMessageDialogImpl*>(this));
    return QDialog::qt_metacast(_clname);
}

int myMessageDialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
