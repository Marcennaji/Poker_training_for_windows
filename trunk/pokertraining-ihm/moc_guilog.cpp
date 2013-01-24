/****************************************************************************
** Meta object code from reading C++ file 'guilog.h'
**
** Created: Sat 12. Jan 12:36:59 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qt/gametable/log/guilog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guilog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_guiLog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: signature, parameters, type, tag, flags
      35,    8,    7,    7, 0x05,
      91,   77,    7,    7, 0x05,
     150,  124,    7,    7, 0x05,
     221,  201,    7,    7, 0x05,
     300,  262,    7,    7, 0x05,
     384,  352,    7,    7, 0x25,
     458,  432,    7,    7, 0x25,
     547,  502,    7,    7, 0x05,
     639,  602,    7,    7, 0x25,
     709,  686,    7,    7, 0x25,
     773,  752,    7,    7, 0x05,
     820,  809,    7,    7, 0x05,
     854,  809,    7,    7, 0x05,
     906,  888,    7,    7, 0x05,
     949,  942,    7,    7, 0x05,
     975,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     998,    8,    7,    7, 0x0a,
    1034,   77,    7,    7, 0x0a,
    1061,  124,    7,    7, 0x0a,
    1106,  201,    7,    7, 0x0a,
    1141,  262,    7,    7, 0x0a,
    1187,  352,    7,    7, 0x2a,
    1229,  432,    7,    7, 0x2a,
    1267,  502,    7,    7, 0x0a,
    1316,  602,    7,    7, 0x2a,
    1357,  686,    7,    7, 0x2a,
    1394,  752,    7,    7, 0x0a,
    1424,  809,    7,    7, 0x0a,
    1452,  809,    7,    7, 0x0a,
    1480,  888,    7,    7, 0x0a,
    1510,  942,    7,    7, 0x0a,
    1530,    7,    7,    7, 0x0a,
    1578, 1547,    7,    7, 0x0a,
    1614, 1547,    7,    7, 0x0a,
    1666, 1649,    7,    7, 0x0a,
    1721, 1701, 1697,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_guiLog[] = {
    "guiLog\0\0playerName,action,setValue\0"
    "signalLogPlayerActionMsg(QString,int,int)\0"
    "gameID,handID\0signalLogNewGameHandMsg(int,int)\0"
    "sbSet,bbSet,sbName,bbName\0"
    "signalLogNewBlindsSetsMsg(int,int,QString,QString)\0"
    "playerName,pot,main\0"
    "signalLogPlayerWinsMsg(QString,int,bool)\0"
    "roundID,card1,card2,card3,card4,card5\0"
    "signalLogDealBoardCardsMsg(int,int,int,int,int,int)\0"
    "roundID,card1,card2,card3,card4\0"
    "signalLogDealBoardCardsMsg(int,int,int,int,int)\0"
    "roundID,card1,card2,card3\0"
    "signalLogDealBoardCardsMsg(int,int,int,int)\0"
    "playerName,card1,card2,cardsValueInt,showHas\0"
    "signalLogFlipHoleCardsMsg(QString,int,int,int,QString)\0"
    "playerName,card1,card2,cardsValueInt\0"
    "signalLogFlipHoleCardsMsg(QString,int,int,int)\0"
    "playerName,card1,card2\0"
    "signalLogFlipHoleCardsMsg(QString,int,int)\0"
    "playerName,wasKicked\0"
    "signalLogPlayerLeftMsg(QString,int)\0"
    "playerName\0signalLogPlayerJoinedMsg(QString)\0"
    "signalLogNewGameAdminMsg(QString)\0"
    "playerName,gameID\0signalLogPlayerWinGame(QString,int)\0"
    "gameID\0signalFlushLogAtGame(int)\0"
    "signalFlushLogAtHand()\0"
    "logPlayerActionMsg(QString,int,int)\0"
    "logNewGameHandMsg(int,int)\0"
    "logNewBlindsSetsMsg(int,int,QString,QString)\0"
    "logPlayerWinsMsg(QString,int,bool)\0"
    "logDealBoardCardsMsg(int,int,int,int,int,int)\0"
    "logDealBoardCardsMsg(int,int,int,int,int)\0"
    "logDealBoardCardsMsg(int,int,int,int)\0"
    "logFlipHoleCardsMsg(QString,int,int,int,QString)\0"
    "logFlipHoleCardsMsg(QString,int,int,int)\0"
    "logFlipHoleCardsMsg(QString,int,int)\0"
    "logPlayerLeftMsg(QString,int)\0"
    "logPlayerJoinedMsg(QString)\0"
    "logNewGameAdminMsg(QString)\0"
    "logPlayerWinGame(QString,int)\0"
    "flushLogAtGame(int)\0flushLogAtHand()\0"
    "fileStringPdb,exportFileString\0"
    "exportLogPdbToHtml(QString,QString)\0"
    "exportLogPdbToTxt(QString,QString)\0"
    "fileStringPdb,tb\0showLog(QString,QTextBrowser*)\0"
    "int\0fileStringPdb,modus\0exportLog(QString,int)\0"
};

void guiLog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        guiLog *_t = static_cast<guiLog *>(_o);
        switch (_id) {
        case 0: _t->signalLogPlayerActionMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->signalLogNewGameHandMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->signalLogNewBlindsSetsMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->signalLogPlayerWinsMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: _t->signalLogDealBoardCardsMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 5: _t->signalLogDealBoardCardsMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 6: _t->signalLogDealBoardCardsMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 7: _t->signalLogFlipHoleCardsMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 8: _t->signalLogFlipHoleCardsMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 9: _t->signalLogFlipHoleCardsMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->signalLogPlayerLeftMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->signalLogPlayerJoinedMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->signalLogNewGameAdminMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->signalLogPlayerWinGame((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->signalFlushLogAtGame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->signalFlushLogAtHand(); break;
        case 16: _t->logPlayerActionMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: _t->logNewGameHandMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->logNewBlindsSetsMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 19: _t->logPlayerWinsMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 20: _t->logDealBoardCardsMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 21: _t->logDealBoardCardsMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 22: _t->logDealBoardCardsMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 23: _t->logFlipHoleCardsMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 24: _t->logFlipHoleCardsMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 25: _t->logFlipHoleCardsMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 26: _t->logPlayerLeftMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 27: _t->logPlayerJoinedMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: _t->logNewGameAdminMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 29: _t->logPlayerWinGame((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 30: _t->flushLogAtGame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->flushLogAtHand(); break;
        case 32: _t->exportLogPdbToHtml((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 33: _t->exportLogPdbToTxt((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 34: _t->showLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QTextBrowser*(*)>(_a[2]))); break;
        case 35: { int _r = _t->exportLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData guiLog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject guiLog::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_guiLog,
      qt_meta_data_guiLog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &guiLog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *guiLog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *guiLog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_guiLog))
        return static_cast<void*>(const_cast< guiLog*>(this));
    return QObject::qt_metacast(_clname);
}

int guiLog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    }
    return _id;
}

// SIGNAL 0
void guiLog::signalLogPlayerActionMsg(QString _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void guiLog::signalLogNewGameHandMsg(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void guiLog::signalLogNewBlindsSetsMsg(int _t1, int _t2, QString _t3, QString _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void guiLog::signalLogPlayerWinsMsg(QString _t1, int _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void guiLog::signalLogDealBoardCardsMsg(int _t1, int _t2, int _t3, int _t4, int _t5, int _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 7
void guiLog::signalLogFlipHoleCardsMsg(QString _t1, int _t2, int _t3, int _t4, QString _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 10
void guiLog::signalLogPlayerLeftMsg(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void guiLog::signalLogPlayerJoinedMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void guiLog::signalLogNewGameAdminMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void guiLog::signalLogPlayerWinGame(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void guiLog::signalFlushLogAtGame(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void guiLog::signalFlushLogAtHand()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}
QT_END_MOC_NAMESPACE
