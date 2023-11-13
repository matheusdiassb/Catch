/****************************************************************************
** Meta object code from reading C++ file 'Catch.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Catch/Catch.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Catch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Catch_t {
    QByteArrayData data[13];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Catch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Catch_t qt_meta_stringdata_Catch = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Catch"
QT_MOC_LITERAL(1, 6, 9), // "turnEnded"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "gameOver"
QT_MOC_LITERAL(4, 26, 4), // "play"
QT_MOC_LITERAL(5, 31, 2), // "id"
QT_MOC_LITERAL(6, 34, 12), // "switchPlayer"
QT_MOC_LITERAL(7, 47, 5), // "reset"
QT_MOC_LITERAL(8, 53, 12), // "showGameOver"
QT_MOC_LITERAL(9, 66, 9), // "showAbout"
QT_MOC_LITERAL(10, 76, 17), // "updateSelectables"
QT_MOC_LITERAL(11, 94, 4), // "over"
QT_MOC_LITERAL(12, 99, 15) // "updateStatusBar"

    },
    "Catch\0turnEnded\0\0gameOver\0play\0id\0"
    "switchPlayer\0reset\0showGameOver\0"
    "showAbout\0updateSelectables\0over\0"
    "updateStatusBar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Catch[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   61,    2, 0x08 /* Private */,
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    1,   68,    2, 0x08 /* Private */,
      12,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,

       0        // eod
};

void Catch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Catch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->turnEnded(); break;
        case 1: _t->gameOver(); break;
        case 2: _t->play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->switchPlayer(); break;
        case 4: _t->reset(); break;
        case 5: _t->showGameOver(); break;
        case 6: _t->showAbout(); break;
        case 7: _t->updateSelectables((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->updateStatusBar(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Catch::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Catch::turnEnded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Catch::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Catch::gameOver)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Catch::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Catch.data,
    qt_meta_data_Catch,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Catch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Catch::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Catch.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Catch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Catch::turnEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Catch::gameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
