/****************************************************************************
** Meta object code from reading C++ file 'timeline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../timeline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timeline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Timeline_t {
    QByteArrayData data[13];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Timeline_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Timeline_t qt_meta_stringdata_Timeline = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Timeline"
QT_MOC_LITERAL(1, 9, 13), // "signalDisplay"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "intPos"
QT_MOC_LITERAL(4, 31, 16), // "signalTimerStart"
QT_MOC_LITERAL(5, 48, 15), // "signalTimerStop"
QT_MOC_LITERAL(6, 64, 16), // "signalTimerReset"
QT_MOC_LITERAL(7, 81, 6), // "zoomIn"
QT_MOC_LITERAL(8, 88, 7), // "zoomOut"
QT_MOC_LITERAL(9, 96, 14), // "startMainTimer"
QT_MOC_LITERAL(10, 111, 13), // "stopMainTimer"
QT_MOC_LITERAL(11, 125, 14), // "resetMainTimer"
QT_MOC_LITERAL(12, 140, 15) // "advanceTimeline"

    },
    "Timeline\0signalDisplay\0\0intPos\0"
    "signalTimerStart\0signalTimerStop\0"
    "signalTimerReset\0zoomIn\0zoomOut\0"
    "startMainTimer\0stopMainTimer\0"
    "resetMainTimer\0advanceTimeline"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Timeline[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,
       5,    0,   68,    2, 0x06 /* Public */,
       6,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Timeline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Timeline *_t = static_cast<Timeline *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalDisplay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalTimerStart(); break;
        case 2: _t->signalTimerStop(); break;
        case 3: _t->signalTimerReset(); break;
        case 4: _t->zoomIn(); break;
        case 5: _t->zoomOut(); break;
        case 6: _t->startMainTimer(); break;
        case 7: _t->stopMainTimer(); break;
        case 8: _t->resetMainTimer(); break;
        case 9: _t->advanceTimeline((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Timeline::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Timeline::signalDisplay)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Timeline::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Timeline::signalTimerStart)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Timeline::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Timeline::signalTimerStop)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Timeline::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Timeline::signalTimerReset)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Timeline::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Timeline.data,
      qt_meta_data_Timeline,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Timeline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Timeline::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Timeline.stringdata0))
        return static_cast<void*>(const_cast< Timeline*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Timeline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Timeline::signalDisplay(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Timeline::signalTimerStart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Timeline::signalTimerStop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Timeline::signalTimerReset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
