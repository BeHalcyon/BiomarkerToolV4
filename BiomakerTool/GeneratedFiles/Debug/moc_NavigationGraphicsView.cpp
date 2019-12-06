/****************************************************************************
** Meta object code from reading C++ file 'NavigationGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../NavigationGraphicsView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NavigationGraphicsView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NavigationGraphicsView_t {
    QByteArrayData data[17];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NavigationGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NavigationGraphicsView_t qt_meta_stringdata_NavigationGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 22), // "NavigationGraphicsView"
QT_MOC_LITERAL(1, 23, 15), // "sendCenterPoint"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 11), // "centerPoint"
QT_MOC_LITERAL(4, 52, 26), // "setShowNavigationMinWindow"
QT_MOC_LITERAL(5, 79, 11), // "globalPoint"
QT_MOC_LITERAL(6, 91, 14), // "setZoomInState"
QT_MOC_LITERAL(7, 106, 5), // "state"
QT_MOC_LITERAL(8, 112, 16), // "getGraphicsItems"
QT_MOC_LITERAL(9, 129, 22), // "QList<QGraphicsItem*>&"
QT_MOC_LITERAL(10, 152, 5), // "items"
QT_MOC_LITERAL(11, 158, 14), // "setMakerNumber"
QT_MOC_LITERAL(12, 173, 23), // "QVector<QVector<int> >*"
QT_MOC_LITERAL(13, 197, 18), // "zoomOutMakerNumber"
QT_MOC_LITERAL(14, 216, 17), // "zoomInMakerNumber"
QT_MOC_LITERAL(15, 234, 10), // "setPenType"
QT_MOC_LITERAL(16, 245, 7) // "penType"

    },
    "NavigationGraphicsView\0sendCenterPoint\0"
    "\0centerPoint\0setShowNavigationMinWindow\0"
    "globalPoint\0setZoomInState\0state\0"
    "getGraphicsItems\0QList<QGraphicsItem*>&\0"
    "items\0setMakerNumber\0QVector<QVector<int> >*\0"
    "zoomOutMakerNumber\0zoomInMakerNumber\0"
    "setPenType\0penType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NavigationGraphicsView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x0a /* Public */,
       6,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,
      11,    2,   56,    2, 0x0a /* Public */,
      15,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QPointF,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 12,   13,   14,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

void NavigationGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NavigationGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendCenterPoint((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->setShowNavigationMinWindow((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 2: _t->setZoomInState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->getGraphicsItems((*reinterpret_cast< QList<QGraphicsItem*>(*)>(_a[1]))); break;
        case 4: _t->setMakerNumber((*reinterpret_cast< QVector<QVector<int> >*(*)>(_a[1])),(*reinterpret_cast< QVector<QVector<int> >*(*)>(_a[2]))); break;
        case 5: _t->setPenType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NavigationGraphicsView::*)(QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationGraphicsView::sendCenterPoint)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NavigationGraphicsView::staticMetaObject = { {
    &QGraphicsView::staticMetaObject,
    qt_meta_stringdata_NavigationGraphicsView.data,
    qt_meta_data_NavigationGraphicsView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NavigationGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavigationGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NavigationGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int NavigationGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NavigationGraphicsView::sendCenterPoint(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
