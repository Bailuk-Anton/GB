/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../project/subcomponents/Client/src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "refreshFirstTab"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "refreshSecondTab"
QT_MOC_LITERAL(4, 45, 15), // "refreshThirdTab"
QT_MOC_LITERAL(5, 61, 16), // "refreshFourthTab"
QT_MOC_LITERAL(6, 78, 19), // "onEditButtonClicked"
QT_MOC_LITERAL(7, 98, 2), // "id"
QT_MOC_LITERAL(8, 101, 3), // "row"
QT_MOC_LITERAL(9, 105, 13), // "QTableWidget*"
QT_MOC_LITERAL(10, 119, 5), // "table"
QT_MOC_LITERAL(11, 125, 19), // "onBookButtonClicked"
QT_MOC_LITERAL(12, 145, 7), // "service"
QT_MOC_LITERAL(13, 153, 17), // "QMap<int,QString>"
QT_MOC_LITERAL(14, 171, 8), // "services"
QT_MOC_LITERAL(15, 180, 9) // "loadPhoto"

    },
    "MainWindow\0refreshFirstTab\0\0"
    "refreshSecondTab\0refreshThirdTab\0"
    "refreshFourthTab\0onEditButtonClicked\0"
    "id\0row\0QTableWidget*\0table\0"
    "onBookButtonClicked\0service\0"
    "QMap<int,QString>\0services\0loadPhoto"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    3,   53,    2, 0x08 /* Private */,
      11,    2,   60,    2, 0x08 /* Private */,
      15,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 9,    7,    8,   10,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13,   12,   14,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refreshFirstTab(); break;
        case 1: _t->refreshSecondTab(); break;
        case 2: _t->refreshThirdTab(); break;
        case 3: _t->refreshFourthTab(); break;
        case 4: _t->onEditButtonClicked((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QTableWidget*(*)>(_a[3]))); break;
        case 5: _t->onBookButtonClicked((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QMap<int,QString>(*)>(_a[2]))); break;
        case 6: _t->loadPhoto(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTableWidget* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
