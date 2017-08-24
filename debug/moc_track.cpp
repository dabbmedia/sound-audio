/****************************************************************************
** Meta object code from reading C++ file 'track.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../track.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'track.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Track_t {
    QByteArrayData data[17];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Track_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Track_t qt_meta_stringdata_Track = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Track"
QT_MOC_LITERAL(1, 6, 13), // "processBuffer"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "QAudioBuffer"
QT_MOC_LITERAL(4, 34, 11), // "togglePause"
QT_MOC_LITERAL(5, 46, 12), // "toggleRecord"
QT_MOC_LITERAL(6, 59, 10), // "togglePlay"
QT_MOC_LITERAL(7, 70, 18), // "handleStateChanged"
QT_MOC_LITERAL(8, 89, 13), // "QAudio::State"
QT_MOC_LITERAL(9, 103, 8), // "newState"
QT_MOC_LITERAL(10, 112, 12), // "updateStatus"
QT_MOC_LITERAL(11, 125, 22), // "QMediaRecorder::Status"
QT_MOC_LITERAL(12, 148, 14), // "onStateChanged"
QT_MOC_LITERAL(13, 163, 21), // "QMediaRecorder::State"
QT_MOC_LITERAL(14, 185, 14), // "updateProgress"
QT_MOC_LITERAL(15, 200, 3), // "pos"
QT_MOC_LITERAL(16, 204, 19) // "displayErrorMessage"

    },
    "Track\0processBuffer\0\0QAudioBuffer\0"
    "togglePause\0toggleRecord\0togglePlay\0"
    "handleStateChanged\0QAudio::State\0"
    "newState\0updateStatus\0QMediaRecorder::Status\0"
    "onStateChanged\0QMediaRecorder::State\0"
    "updateProgress\0pos\0displayErrorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Track[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    0,   62,    2, 0x0a /* Public */,
       5,    0,   63,    2, 0x0a /* Public */,
       6,    0,   64,    2, 0x0a /* Public */,
       7,    1,   65,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x08 /* Private */,
      12,    1,   71,    2, 0x08 /* Private */,
      14,    1,   74,    2, 0x08 /* Private */,
      16,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, QMetaType::LongLong,   15,
    QMetaType::Void,

       0        // eod
};

void Track::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Track *_t = static_cast<Track *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processBuffer((*reinterpret_cast< const QAudioBuffer(*)>(_a[1]))); break;
        case 1: _t->togglePause(); break;
        case 2: _t->toggleRecord(); break;
        case 3: _t->togglePlay(); break;
        case 4: _t->handleStateChanged((*reinterpret_cast< QAudio::State(*)>(_a[1]))); break;
        case 5: _t->updateStatus((*reinterpret_cast< QMediaRecorder::Status(*)>(_a[1]))); break;
        case 6: _t->onStateChanged((*reinterpret_cast< QMediaRecorder::State(*)>(_a[1]))); break;
        case 7: _t->updateProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->displayErrorMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudioBuffer >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::State >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaRecorder::Status >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaRecorder::State >(); break;
            }
            break;
        }
    }
}

const QMetaObject Track::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Track.data,
      qt_meta_data_Track,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Track::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Track::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Track.stringdata0))
        return static_cast<void*>(const_cast< Track*>(this));
    return QObject::qt_metacast(_clname);
}

int Track::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
