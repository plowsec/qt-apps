/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../untitled/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 6),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 7),
QT_MOC_LITERAL(4, 27, 3),
QT_MOC_LITERAL(5, 31, 7),
QT_MOC_LITERAL(6, 39, 14),
QT_MOC_LITERAL(7, 54, 11),
QT_MOC_LITERAL(8, 66, 5),
QT_MOC_LITERAL(9, 72, 7),
QT_MOC_LITERAL(10, 80, 9),
QT_MOC_LITERAL(11, 90, 10),
QT_MOC_LITERAL(12, 101, 1),
QT_MOC_LITERAL(13, 103, 5),
QT_MOC_LITERAL(14, 109, 10),
QT_MOC_LITERAL(15, 120, 7),
QT_MOC_LITERAL(16, 128, 9),
QT_MOC_LITERAL(17, 138, 1),
QT_MOC_LITERAL(18, 140, 1),
QT_MOC_LITERAL(19, 142, 4),
QT_MOC_LITERAL(20, 147, 7),
QT_MOC_LITERAL(21, 155, 8)
    },
    "MainWindow\0reset1\0\0addText\0str\0remplir\0"
    "remplirLettres\0listSymbols\0solve\0"
    "freeRow\0int[9][9]\0grilleTest\0n\0ligne\0"
    "freeColumn\0colonne\0freeBlock\0i\0j\0Free\0"
    "isValid\0position"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    1,   70,    2, 0x08 /* Private */,
       5,    0,   73,    2, 0x08 /* Private */,
       6,    0,   74,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    3,   77,    2, 0x08 /* Private */,
      14,    3,   84,    2, 0x08 /* Private */,
      16,    4,   91,    2, 0x08 /* Private */,
      19,    4,  100,    2, 0x08 /* Private */,
      20,    2,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 10, QMetaType::Int, QMetaType::Int,   11,   12,   13,
    QMetaType::Bool, 0x80000000 | 10, QMetaType::Int, QMetaType::Int,   11,   12,   15,
    QMetaType::Bool, 0x80000000 | 10, QMetaType::Int, QMetaType::Int, QMetaType::Int,   11,   12,   17,   18,
    QMetaType::Bool, 0x80000000 | 10, QMetaType::Int, QMetaType::Int, QMetaType::Int,   11,   12,   17,   18,
    QMetaType::Bool, 0x80000000 | 10, QMetaType::Int,   11,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->reset1(); break;
        case 1: _t->addText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->remplir(); break;
        case 3: _t->remplirLettres(); break;
        case 4: { QString _r = _t->listSymbols();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: _t->solve(); break;
        case 6: { bool _r = _t->freeRow((*reinterpret_cast< int(*)[9][9]>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->freeColumn((*reinterpret_cast< int(*)[9][9]>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->freeBlock((*reinterpret_cast< int(*)[9][9]>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->Free((*reinterpret_cast< int(*)[9][9]>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->isValid((*reinterpret_cast< int(*)[9][9]>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
