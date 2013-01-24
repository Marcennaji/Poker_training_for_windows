/****************************************************************************
** Meta object code from reading C++ file 'mycardspixmaplabel.h'
**
** Created: Sat 12. Jan 12:36:48 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/gametable/mycardspixmaplabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mycardspixmaplabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyCardsPixmapLabel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   46,   19,   19, 0x0a,
      72,   19,   19,   19, 0x0a,
     102,   19,   19,   19, 0x0a,
     121,   19,   19,   19, 0x0a,
     148,  142,   19,   19, 0x0a,
     168,   19,   19,   19, 0x0a,
     198,   19,   19,   19, 0x0a,
     239,  230,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyCardsPixmapLabel[] = {
    "MyCardsPixmapLabel\0\0signalFastFlipCards(bool)\0"
    ",\0setPixmap(QPixmap,bool)\0"
    "setHiddenFrontPixmap(QPixmap)\0"
    "nextFadeOutFrame()\0nextFlipCardsFrame()\0"
    "front\0fastFlipCards(bool)\0"
    "mousePressEvent(QMouseEvent*)\0"
    "mouseReleaseEvent(QMouseEvent*)\0"
    "theValue\0setFront(QPixmap)\0"
};

void MyCardsPixmapLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyCardsPixmapLabel *_t = static_cast<MyCardsPixmapLabel *>(_o);
        switch (_id) {
        case 0: _t->signalFastFlipCards((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setPixmap((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 2: _t->setHiddenFrontPixmap((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 3: _t->nextFadeOutFrame(); break;
        case 4: _t->nextFlipCardsFrame(); break;
        case 5: _t->fastFlipCards((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->setFront((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyCardsPixmapLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyCardsPixmapLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_MyCardsPixmapLabel,
      qt_meta_data_MyCardsPixmapLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyCardsPixmapLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyCardsPixmapLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyCardsPixmapLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyCardsPixmapLabel))
        return static_cast<void*>(const_cast< MyCardsPixmapLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int MyCardsPixmapLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MyCardsPixmapLabel::signalFastFlipCards(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
