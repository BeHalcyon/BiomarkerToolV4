/****************************************************************************
** Meta object code from reading C++ file 'GlobalGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GlobalGraphicsView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GlobalGraphicsView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GlobalGraphicsView_t {
    QByteArrayData data[21];
    char stringdata0[408];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GlobalGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GlobalGraphicsView_t qt_meta_stringdata_GlobalGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 18), // "GlobalGraphicsView"
QT_MOC_LITERAL(1, 19, 19), // "sendCircleNumberMap"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 35), // "QMap<QGraphicsEllipseItem*,QS..."
QT_MOC_LITERAL(4, 76, 2), // "is"
QT_MOC_LITERAL(5, 79, 18), // "sendShapeNumberMap"
QT_MOC_LITERAL(6, 98, 36), // "QMap<QGraphicsEllipseItem*,QS..."
QT_MOC_LITERAL(7, 135, 33), // "QMap<QGraphicsPathItem*,QStri..."
QT_MOC_LITERAL(8, 169, 3), // "map"
QT_MOC_LITERAL(9, 173, 17), // "sendSelectedShape"
QT_MOC_LITERAL(10, 191, 17), // "circle_number_map"
QT_MOC_LITERAL(11, 209, 32), // "QMap<QGraphicsPathItem*,QString>"
QT_MOC_LITERAL(12, 242, 18), // "polygon_number_map"
QT_MOC_LITERAL(13, 261, 14), // "QGraphicsItem*"
QT_MOC_LITERAL(14, 276, 12), // "selectedItem"
QT_MOC_LITERAL(15, 289, 17), // "sendRemoveCommand"
QT_MOC_LITERAL(16, 307, 18), // "QGraphicsPathItem*"
QT_MOC_LITERAL(17, 326, 18), // "graphics_path_item"
QT_MOC_LITERAL(18, 345, 33), // "sendNewPolygonToLocalGraphics..."
QT_MOC_LITERAL(19, 379, 19), // "QGraphicsPathItem*&"
QT_MOC_LITERAL(20, 399, 8) // "buf_item"

    },
    "GlobalGraphicsView\0sendCircleNumberMap\0"
    "\0QMap<QGraphicsEllipseItem*,QString>\0"
    "is\0sendShapeNumberMap\0"
    "QMap<QGraphicsEllipseItem*,QString>&\0"
    "QMap<QGraphicsPathItem*,QString>&\0map\0"
    "sendSelectedShape\0circle_number_map\0"
    "QMap<QGraphicsPathItem*,QString>\0"
    "polygon_number_map\0QGraphicsItem*\0"
    "selectedItem\0sendRemoveCommand\0"
    "QGraphicsPathItem*\0graphics_path_item\0"
    "sendNewPolygonToLocalGraphicsView\0"
    "QGraphicsPathItem*&\0buf_item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GlobalGraphicsView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    2,   42,    2, 0x06 /* Public */,
       9,    3,   47,    2, 0x06 /* Public */,
      15,    1,   54,    2, 0x06 /* Public */,
      18,    1,   57,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 7,    4,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 11, 0x80000000 | 13,   10,   12,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void GlobalGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GlobalGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendCircleNumberMap((*reinterpret_cast< const QMap<QGraphicsEllipseItem*,QString>(*)>(_a[1]))); break;
        case 1: _t->sendShapeNumberMap((*reinterpret_cast< QMap<QGraphicsEllipseItem*,QString>(*)>(_a[1])),(*reinterpret_cast< QMap<QGraphicsPathItem*,QString>(*)>(_a[2]))); break;
        case 2: _t->sendSelectedShape((*reinterpret_cast< const QMap<QGraphicsEllipseItem*,QString>(*)>(_a[1])),(*reinterpret_cast< const QMap<QGraphicsPathItem*,QString>(*)>(_a[2])),(*reinterpret_cast< QGraphicsItem*(*)>(_a[3]))); break;
        case 3: _t->sendRemoveCommand((*reinterpret_cast< QGraphicsPathItem*(*)>(_a[1]))); break;
        case 4: _t->sendNewPolygonToLocalGraphicsView((*reinterpret_cast< QGraphicsPathItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GlobalGraphicsView::*)(const QMap<QGraphicsEllipseItem*,QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GlobalGraphicsView::sendCircleNumberMap)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GlobalGraphicsView::*)(QMap<QGraphicsEllipseItem*,QString> & , QMap<QGraphicsPathItem*,QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GlobalGraphicsView::sendShapeNumberMap)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GlobalGraphicsView::*)(const QMap<QGraphicsEllipseItem*,QString> & , const QMap<QGraphicsPathItem*,QString> & , QGraphicsItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GlobalGraphicsView::sendSelectedShape)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GlobalGraphicsView::*)(QGraphicsPathItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GlobalGraphicsView::sendRemoveCommand)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GlobalGraphicsView::*)(QGraphicsPathItem * & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GlobalGraphicsView::sendNewPolygonToLocalGraphicsView)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GlobalGraphicsView::staticMetaObject = { {
    &QGraphicsView::staticMetaObject,
    qt_meta_stringdata_GlobalGraphicsView.data,
    qt_meta_data_GlobalGraphicsView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GlobalGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GlobalGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GlobalGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int GlobalGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GlobalGraphicsView::sendCircleNumberMap(const QMap<QGraphicsEllipseItem*,QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GlobalGraphicsView::sendShapeNumberMap(QMap<QGraphicsEllipseItem*,QString> & _t1, QMap<QGraphicsPathItem*,QString> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GlobalGraphicsView::sendSelectedShape(const QMap<QGraphicsEllipseItem*,QString> & _t1, const QMap<QGraphicsPathItem*,QString> & _t2, QGraphicsItem * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GlobalGraphicsView::sendRemoveCommand(QGraphicsPathItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GlobalGraphicsView::sendNewPolygonToLocalGraphicsView(QGraphicsPathItem * & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
