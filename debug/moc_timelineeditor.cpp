/****************************************************************************
** Meta object code from reading C++ file 'timelineeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../timelineeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timelineeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TimelineEditor_t {
    QByteArrayData data[13];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimelineEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimelineEditor_t qt_meta_stringdata_TimelineEditor = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TimelineEditor"
QT_MOC_LITERAL(1, 15, 7), // "zoomOut"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "zoomIn"
QT_MOC_LITERAL(4, 31, 18), // "setCurrentPosition"
QT_MOC_LITERAL(5, 50, 6), // "intPos"
QT_MOC_LITERAL(6, 57, 14), // "startMainTimer"
QT_MOC_LITERAL(7, 72, 13), // "stopMainTimer"
QT_MOC_LITERAL(8, 86, 14), // "resetMainTimer"
QT_MOC_LITERAL(9, 101, 8), // "addTrack"
QT_MOC_LITERAL(10, 110, 13), // "newTrackIndex"
QT_MOC_LITERAL(11, 124, 6), // "Track*"
QT_MOC_LITERAL(12, 131, 5) // "track"

    },
    "TimelineEditor\0zoomOut\0\0zoomIn\0"
    "setCurrentPosition\0intPos\0startMainTimer\0"
    "stopMainTimer\0resetMainTimer\0addTrack\0"
    "newTrackIndex\0Track*\0track"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimelineEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    1,   51,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    2,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   10,   12,

       0        // eod
};

void TimelineEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TimelineEditor *_t = static_cast<TimelineEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->zoomOut(); break;
        case 1: _t->zoomIn(); break;
        case 2: _t->setCurrentPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->startMainTimer(); break;
        case 4: _t->stopMainTimer(); break;
        case 5: _t->resetMainTimer(); break;
        case 6: _t->addTrack((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Track*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Track* >(); break;
            }
            break;
        }
    }
}

const QMetaObject TimelineEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TimelineEditor.data,
      qt_meta_data_TimelineEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TimelineEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimelineEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TimelineEditor.stringdata0))
        return static_cast<void*>(const_cast< TimelineEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int TimelineEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
