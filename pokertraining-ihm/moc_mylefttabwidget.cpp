/****************************************************************************
** Meta object code from reading C++ file 'mylefttabwidget.h'
**
** Created: Sat 12. Jan 12:36:50 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/gametable/mylefttabwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mylefttabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyLeftTabWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      41,   16,   32,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyLeftTabWidget[] = {
    "MyLeftTabWidget\0\0blinkChatTab()\0"
    "QTabBar*\0getTabBar()\0"
};

void MyLeftTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyLeftTabWidget *_t = static_cast<MyLeftTabWidget *>(_o);
        switch (_id) {
        case 0: _t->blinkChatTab(); break;
        case 1: { QTabBar* _r = _t->getTabBar();
            if (_a[0]) *reinterpret_cast< QTabBar**>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyLeftTabWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyLeftTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_MyLeftTabWidget,
      qt_meta_data_MyLeftTabWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyLeftTabWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyLeftTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyLeftTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyLeftTabWidget))
        return static_cast<void*>(const_cast< MyLeftTabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int MyLeftTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
