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
    QByteArrayData data[14];
    char stringdata0[175];
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
QT_MOC_LITERAL(3, 24, 16), // "signalTimerStart"
QT_MOC_LITERAL(4, 41, 15), // "signalTimerStop"
QT_MOC_LITERAL(5, 57, 16), // "signalTimerReset"
QT_MOC_LITERAL(6, 74, 16), // "signalTrackAdded"
QT_MOC_LITERAL(7, 91, 6), // "zoomIn"
QT_MOC_LITERAL(8, 98, 7), // "zoomOut"
QT_MOC_LITERAL(9, 106, 14), // "startMainTimer"
QT_MOC_LITERAL(10, 121, 13), // "stopMainTimer"
QT_MOC_LITERAL(11, 135, 14), // "resetMainTimer"
QT_MOC_LITERAL(12, 150, 15), // "advanceTimeline"
QT_MOC_LITERAL(13, 166, 8) // "addTrack"

    },
    "Timeline\0signalDisplay\0\0signalTimerStart\0"
    "signalTimerStop\0signalTimerReset\0"
    "signalTrackAdded\0zoomIn\0zoomOut\0"
    "startMainTimer\0stopMainTimer\0"
    "resetMainTimer\0advanceTimeline\0addTrack"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Timeline[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,
       6,    0,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    1,   84,    2, 0x0a /* Public */,
      13,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
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
    QMetaType::Void,

       0        // eod
};

void Timeline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Timeline *_t = static_cast<Timeline *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalDisplay(); break;
        case 1: _t->signalTimerStart(); break;
        case 2: _t->signalTimerStop(); break;
        case 3: _t->signalTimerReset(); break;
        case 4: _t->signalTrackAdded(); break;
        case 5: _t->zoomIn(); break;
        case 6: _t->zoomOut(); break;
        case 7: _t->startMainTimer(); break;
        case 8: _t->stopMainTimer(); break;
        case 9: _t->resetMainTimer(); break;
        case 10: _t->advanceTimeline((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->addTrack(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Timeline::*_t)();
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
        {
            typedef void (Timeline::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Timeline::signalTrackAdded)) {
                *result = 4;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Timeline::signalDisplay()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
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

// SIGNAL 4
void Timeline::signalTrackAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
