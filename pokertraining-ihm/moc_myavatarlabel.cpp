/****************************************************************************
** Meta object code from reading C++ file 'myavatarlabel.h'
**
** Created: Sat 12. Jan 12:36:47 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/gametable/myavatarlabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myavatarlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyAvatarLabel[] = {

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
      19,   15,   14,   14, 0x0a,
      43,   14,   14,   14, 0x0a,
      73,   71,   14,   14, 0x0a,
      97,   14,   14,   14, 0x2a,
     136,  116,   14,   14, 0x0a,
     201,  182,   14,   14, 0x2a,
     251,  242,   14,   14, 0x0a,
     274,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyAvatarLabel[] = {
    "MyAvatarLabel\0\0pos\0showContextMenu(QPoint)\0"
    "setEnabledContextMenu(bool)\0,\0"
    "setPixmap(QPixmap,bool)\0setPixmap(QPixmap)\0"
    ",country,seatPlace,\0"
    "setPixmapAndCountry(QPixmap,QString,int,bool)\0"
    ",country,seatPlace\0"
    "setPixmapAndCountry(QPixmap,QString,int)\0"
    "theValue\0setPixmapPath(QString)\0"
    "paintEvent(QPaintEvent*)\0"
};

void MyAvatarLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyAvatarLabel *_t = static_cast<MyAvatarLabel *>(_o);
        switch (_id) {
        case 0: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->setEnabledContextMenu((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setPixmap((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 3: _t->setPixmap((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 4: _t->setPixmapAndCountry((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const bool(*)>(_a[4]))); break;
        case 5: _t->setPixmapAndCountry((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->setPixmapPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyAvatarLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyAvatarLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_MyAvatarLabel,
      qt_meta_data_MyAvatarLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyAvatarLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyAvatarLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyAvatarLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyAvatarLabel))
        return static_cast<void*>(const_cast< MyAvatarLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int MyAvatarLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
