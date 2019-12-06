/****************************************************************************
** Meta object code from reading C++ file 'LocalGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LocalGraphicsView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LocalGraphicsView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LocalGraphicsView_t {
    QByteArrayData data[80];
    char stringdata0[1257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LocalGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LocalGraphicsView_t qt_meta_stringdata_LocalGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 17), // "LocalGraphicsView"
QT_MOC_LITERAL(1, 18, 17), // "startPointChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 15), // "sendZoomInState"
QT_MOC_LITERAL(4, 53, 19), // "sendRedLabelNumbers"
QT_MOC_LITERAL(5, 73, 21), // "sendGreenLabelNumbers"
QT_MOC_LITERAL(6, 95, 20), // "sendBlueLabelNumbers"
QT_MOC_LITERAL(7, 116, 22), // "sendYellowLabelNumbers"
QT_MOC_LITERAL(8, 139, 21), // "sendBlackLabelNumbers"
QT_MOC_LITERAL(9, 161, 17), // "sendGraphicsItems"
QT_MOC_LITERAL(10, 179, 22), // "QList<QGraphicsItem*>&"
QT_MOC_LITERAL(11, 202, 15), // "sendMakerNumber"
QT_MOC_LITERAL(12, 218, 23), // "QVector<QVector<int> >*"
QT_MOC_LITERAL(13, 242, 18), // "zoomOutMakerNumber"
QT_MOC_LITERAL(14, 261, 17), // "zoomInMakerNumber"
QT_MOC_LITERAL(15, 279, 11), // "sendPenType"
QT_MOC_LITERAL(16, 291, 26), // "signal_SendCurrentRectItem"
QT_MOC_LITERAL(17, 318, 14), // "QGraphicsItem*"
QT_MOC_LITERAL(18, 333, 4), // "item"
QT_MOC_LITERAL(19, 338, 23), // "signal_SendCheckedState"
QT_MOC_LITERAL(20, 362, 17), // "GraphicsRectItem*"
QT_MOC_LITERAL(21, 380, 1), // "i"
QT_MOC_LITERAL(22, 382, 18), // "sendShapeNumberMap"
QT_MOC_LITERAL(23, 401, 31), // "QMap<QGraphicsEllipseItem*,int>"
QT_MOC_LITERAL(24, 433, 2), // "is"
QT_MOC_LITERAL(25, 436, 28), // "QMap<QGraphicsPathItem*,int>"
QT_MOC_LITERAL(26, 465, 3), // "map"
QT_MOC_LITERAL(27, 469, 17), // "sendSelectedShape"
QT_MOC_LITERAL(28, 487, 17), // "circle_number_map"
QT_MOC_LITERAL(29, 505, 18), // "polygon_number_map"
QT_MOC_LITERAL(30, 524, 12), // "selectedItem"
QT_MOC_LITERAL(31, 537, 11), // "sendPolygon"
QT_MOC_LITERAL(32, 549, 18), // "QGraphicsPathItem*"
QT_MOC_LITERAL(33, 568, 11), // "cur_ploygon"
QT_MOC_LITERAL(34, 580, 5), // "point"
QT_MOC_LITERAL(35, 586, 10), // "sendCircle"
QT_MOC_LITERAL(36, 597, 21), // "QGraphicsEllipseItem*"
QT_MOC_LITERAL(37, 619, 10), // "cur_circle"
QT_MOC_LITERAL(38, 630, 16), // "sendLocalPolygon"
QT_MOC_LITERAL(39, 647, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(40, 664, 6), // "vector"
QT_MOC_LITERAL(41, 671, 9), // "path_item"
QT_MOC_LITERAL(42, 681, 9), // "setZoomIn"
QT_MOC_LITERAL(43, 691, 10), // "setZoomOut"
QT_MOC_LITERAL(44, 702, 9), // "setRedPen"
QT_MOC_LITERAL(45, 712, 11), // "setGreenPen"
QT_MOC_LITERAL(46, 724, 10), // "setBluePen"
QT_MOC_LITERAL(47, 735, 12), // "setYellowPen"
QT_MOC_LITERAL(48, 748, 11), // "setBlackPen"
QT_MOC_LITERAL(49, 760, 6), // "zoomIn"
QT_MOC_LITERAL(50, 767, 7), // "zoomOut"
QT_MOC_LITERAL(51, 775, 4), // "zoom"
QT_MOC_LITERAL(52, 780, 11), // "scaleFactor"
QT_MOC_LITERAL(53, 792, 9), // "translate"
QT_MOC_LITERAL(54, 802, 5), // "delta"
QT_MOC_LITERAL(55, 808, 20), // "circleMouseMoveEvent"
QT_MOC_LITERAL(56, 829, 12), // "QMouseEvent*"
QT_MOC_LITERAL(57, 842, 5), // "event"
QT_MOC_LITERAL(58, 848, 21), // "circleMousePressEvent"
QT_MOC_LITERAL(59, 870, 23), // "circleMouseReleaseEvent"
QT_MOC_LITERAL(60, 894, 21), // "ploygonMouseMoveEvent"
QT_MOC_LITERAL(61, 916, 21), // "getRectCountInPolygon"
QT_MOC_LITERAL(62, 938, 12), // "QPainterPath"
QT_MOC_LITERAL(63, 951, 13), // "graphics_path"
QT_MOC_LITERAL(64, 965, 18), // "updateMarkerNumber"
QT_MOC_LITERAL(65, 984, 24), // "updataCircleMarkerNumber"
QT_MOC_LITERAL(66, 1009, 25), // "updatePolygonMarkerNumber"
QT_MOC_LITERAL(67, 1035, 22), // "ploygonMousePressEvent"
QT_MOC_LITERAL(68, 1058, 24), // "ploygonMouseReleaseEvent"
QT_MOC_LITERAL(69, 1083, 18), // "setCircleDrawState"
QT_MOC_LITERAL(70, 1102, 5), // "state"
QT_MOC_LITERAL(71, 1108, 14), // "setRegionState"
QT_MOC_LITERAL(72, 1123, 16), // "getRemovePolygon"
QT_MOC_LITERAL(73, 1140, 13), // "setNewPolygon"
QT_MOC_LITERAL(74, 1154, 12), // "painter_path"
QT_MOC_LITERAL(75, 1167, 6), // "factor"
QT_MOC_LITERAL(76, 1174, 12), // "width_factor"
QT_MOC_LITERAL(77, 1187, 13), // "height_factor"
QT_MOC_LITERAL(78, 1201, 35), // "setNewPolygonFromGlobalGraphi..."
QT_MOC_LITERAL(79, 1237, 19) // "QGraphicsPathItem*&"

    },
    "LocalGraphicsView\0startPointChanged\0"
    "\0sendZoomInState\0sendRedLabelNumbers\0"
    "sendGreenLabelNumbers\0sendBlueLabelNumbers\0"
    "sendYellowLabelNumbers\0sendBlackLabelNumbers\0"
    "sendGraphicsItems\0QList<QGraphicsItem*>&\0"
    "sendMakerNumber\0QVector<QVector<int> >*\0"
    "zoomOutMakerNumber\0zoomInMakerNumber\0"
    "sendPenType\0signal_SendCurrentRectItem\0"
    "QGraphicsItem*\0item\0signal_SendCheckedState\0"
    "GraphicsRectItem*\0i\0sendShapeNumberMap\0"
    "QMap<QGraphicsEllipseItem*,int>\0is\0"
    "QMap<QGraphicsPathItem*,int>\0map\0"
    "sendSelectedShape\0circle_number_map\0"
    "polygon_number_map\0selectedItem\0"
    "sendPolygon\0QGraphicsPathItem*\0"
    "cur_ploygon\0point\0sendCircle\0"
    "QGraphicsEllipseItem*\0cur_circle\0"
    "sendLocalPolygon\0QVector<QPointF>\0"
    "vector\0path_item\0setZoomIn\0setZoomOut\0"
    "setRedPen\0setGreenPen\0setBluePen\0"
    "setYellowPen\0setBlackPen\0zoomIn\0zoomOut\0"
    "zoom\0scaleFactor\0translate\0delta\0"
    "circleMouseMoveEvent\0QMouseEvent*\0"
    "event\0circleMousePressEvent\0"
    "circleMouseReleaseEvent\0ploygonMouseMoveEvent\0"
    "getRectCountInPolygon\0QPainterPath\0"
    "graphics_path\0updateMarkerNumber\0"
    "updataCircleMarkerNumber\0"
    "updatePolygonMarkerNumber\0"
    "ploygonMousePressEvent\0ploygonMouseReleaseEvent\0"
    "setCircleDrawState\0state\0setRegionState\0"
    "getRemovePolygon\0setNewPolygon\0"
    "painter_path\0factor\0width_factor\0"
    "height_factor\0setNewPolygonFromGlobalGraphicsView\0"
    "QGraphicsPathItem*&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LocalGraphicsView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      44,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  234,    2, 0x06 /* Public */,
       3,    1,  237,    2, 0x06 /* Public */,
       4,    1,  240,    2, 0x06 /* Public */,
       5,    1,  243,    2, 0x06 /* Public */,
       6,    1,  246,    2, 0x06 /* Public */,
       7,    1,  249,    2, 0x06 /* Public */,
       8,    1,  252,    2, 0x06 /* Public */,
       9,    1,  255,    2, 0x06 /* Public */,
      11,    2,  258,    2, 0x06 /* Public */,
      15,    1,  263,    2, 0x06 /* Public */,
      16,    1,  266,    2, 0x06 /* Public */,
      19,    2,  269,    2, 0x06 /* Public */,
      22,    2,  274,    2, 0x06 /* Public */,
      27,    3,  279,    2, 0x06 /* Public */,
      31,    2,  286,    2, 0x06 /* Public */,
      35,    2,  291,    2, 0x06 /* Public */,
      38,    2,  296,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      42,    0,  301,    2, 0x0a /* Public */,
      43,    0,  302,    2, 0x0a /* Public */,
      44,    0,  303,    2, 0x0a /* Public */,
      45,    0,  304,    2, 0x0a /* Public */,
      46,    0,  305,    2, 0x0a /* Public */,
      47,    0,  306,    2, 0x0a /* Public */,
      48,    0,  307,    2, 0x0a /* Public */,
      49,    0,  308,    2, 0x0a /* Public */,
      50,    0,  309,    2, 0x0a /* Public */,
      51,    1,  310,    2, 0x0a /* Public */,
      53,    1,  313,    2, 0x0a /* Public */,
      55,    1,  316,    2, 0x0a /* Public */,
      58,    1,  319,    2, 0x0a /* Public */,
      59,    1,  322,    2, 0x0a /* Public */,
      60,    1,  325,    2, 0x0a /* Public */,
      61,    1,  328,    2, 0x0a /* Public */,
      64,    0,  331,    2, 0x0a /* Public */,
      65,    0,  332,    2, 0x0a /* Public */,
      66,    0,  333,    2, 0x0a /* Public */,
      67,    1,  334,    2, 0x0a /* Public */,
      68,    1,  337,    2, 0x0a /* Public */,
      69,    1,  340,    2, 0x0a /* Public */,
      71,    1,  343,    2, 0x0a /* Public */,
      72,    1,  346,    2, 0x0a /* Public */,
      73,    2,  349,    2, 0x0a /* Public */,
      73,    3,  354,    2, 0x0a /* Public */,
      78,    1,  361,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 12,   13,   14,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20, QMetaType::Int,   18,   21,
    QMetaType::Void, 0x80000000 | 23, 0x80000000 | 25,   24,   26,
    QMetaType::Void, 0x80000000 | 23, 0x80000000 | 25, 0x80000000 | 17,   28,   29,   30,
    QMetaType::Void, 0x80000000 | 32, QMetaType::QPoint,   33,   34,
    QMetaType::Void, 0x80000000 | 36, QMetaType::QPoint,   37,   34,
    QMetaType::Void, 0x80000000 | 39, 0x80000000 | 32,   40,   41,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,   52,
    QMetaType::Void, QMetaType::QPointF,   54,
    QMetaType::Void, 0x80000000 | 56,   57,
    QMetaType::Void, 0x80000000 | 56,   57,
    QMetaType::Void, 0x80000000 | 56,   57,
    QMetaType::Void, 0x80000000 | 56,   57,
    QMetaType::Int, 0x80000000 | 62,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 56,   57,
    QMetaType::Void, 0x80000000 | 56,   57,
    QMetaType::Void, QMetaType::Bool,   70,
    QMetaType::Void, QMetaType::Bool,   70,
    QMetaType::Void, 0x80000000 | 32,   18,
    QMetaType::Void, 0x80000000 | 62, QMetaType::Double,   74,   75,
    QMetaType::Void, 0x80000000 | 62, QMetaType::Double, QMetaType::Double,   74,   76,   77,
    QMetaType::Void, 0x80000000 | 79,   18,

       0        // eod
};

void LocalGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LocalGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startPointChanged((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->sendZoomInState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sendRedLabelNumbers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sendGreenLabelNumbers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sendBlueLabelNumbers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sendYellowLabelNumbers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sendBlackLabelNumbers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->sendGraphicsItems((*reinterpret_cast< QList<QGraphicsItem*>(*)>(_a[1]))); break;
        case 8: _t->sendMakerNumber((*reinterpret_cast< QVector<QVector<int> >*(*)>(_a[1])),(*reinterpret_cast< QVector<QVector<int> >*(*)>(_a[2]))); break;
        case 9: _t->sendPenType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->signal_SendCurrentRectItem((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        case 11: _t->signal_SendCheckedState((*reinterpret_cast< GraphicsRectItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->sendShapeNumberMap((*reinterpret_cast< const QMap<QGraphicsEllipseItem*,int>(*)>(_a[1])),(*reinterpret_cast< const QMap<QGraphicsPathItem*,int>(*)>(_a[2]))); break;
        case 13: _t->sendSelectedShape((*reinterpret_cast< const QMap<QGraphicsEllipseItem*,int>(*)>(_a[1])),(*reinterpret_cast< const QMap<QGraphicsPathItem*,int>(*)>(_a[2])),(*reinterpret_cast< QGraphicsItem*(*)>(_a[3]))); break;
        case 14: _t->sendPolygon((*reinterpret_cast< QGraphicsPathItem*(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 15: _t->sendCircle((*reinterpret_cast< QGraphicsEllipseItem*(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 16: _t->sendLocalPolygon((*reinterpret_cast< const QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< QGraphicsPathItem*(*)>(_a[2]))); break;
        case 17: _t->setZoomIn(); break;
        case 18: _t->setZoomOut(); break;
        case 19: _t->setRedPen(); break;
        case 20: _t->setGreenPen(); break;
        case 21: _t->setBluePen(); break;
        case 22: _t->setYellowPen(); break;
        case 23: _t->setBlackPen(); break;
        case 24: _t->zoomIn(); break;
        case 25: _t->zoomOut(); break;
        case 26: _t->zoom((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 27: _t->translate((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 28: _t->circleMouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 29: _t->circleMousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 30: _t->circleMouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 31: _t->ploygonMouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 32: { int _r = _t->getRectCountInPolygon((*reinterpret_cast< QPainterPath(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->updateMarkerNumber(); break;
        case 34: _t->updataCircleMarkerNumber(); break;
        case 35: _t->updatePolygonMarkerNumber(); break;
        case 36: _t->ploygonMousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 37: _t->ploygonMouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 38: _t->setCircleDrawState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->setRegionState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->getRemovePolygon((*reinterpret_cast< QGraphicsPathItem*(*)>(_a[1]))); break;
        case 41: _t->setNewPolygon((*reinterpret_cast< QPainterPath(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 42: _t->setNewPolygon((*reinterpret_cast< QPainterPath(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 43: _t->setNewPolygonFromGlobalGraphicsView((*reinterpret_cast< QGraphicsPathItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LocalGraphicsView::*)(QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::startPointChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendZoomInState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendRedLabelNumbers)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendGreenLabelNumbers)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendBlueLabelNumbers)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendYellowLabelNumbers)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendBlackLabelNumbers)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(QList<QGraphicsItem*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendGraphicsItems)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(QVector<QVector<int>> * , QVector<QVector<int>> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendMakerNumber)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendPenType)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(QGraphicsItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::signal_SendCurrentRectItem)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(GraphicsRectItem * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::signal_SendCheckedState)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(const QMap<QGraphicsEllipseItem*,int> & , const QMap<QGraphicsPathItem*,int> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendShapeNumberMap)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(const QMap<QGraphicsEllipseItem*,int> & , const QMap<QGraphicsPathItem*,int> & , QGraphicsItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendSelectedShape)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(QGraphicsPathItem * , const QPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendPolygon)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(QGraphicsEllipseItem * , const QPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendCircle)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (LocalGraphicsView::*)(const QVector<QPointF> & , QGraphicsPathItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalGraphicsView::sendLocalPolygon)) {
                *result = 16;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LocalGraphicsView::staticMetaObject = { {
    &QGraphicsView::staticMetaObject,
    qt_meta_stringdata_LocalGraphicsView.data,
    qt_meta_data_LocalGraphicsView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LocalGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LocalGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LocalGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int LocalGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    }
    return _id;
}

// SIGNAL 0
void LocalGraphicsView::startPointChanged(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalGraphicsView::sendZoomInState(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalGraphicsView::sendRedLabelNumbers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LocalGraphicsView::sendGreenLabelNumbers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LocalGraphicsView::sendBlueLabelNumbers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LocalGraphicsView::sendYellowLabelNumbers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LocalGraphicsView::sendBlackLabelNumbers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void LocalGraphicsView::sendGraphicsItems(QList<QGraphicsItem*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void LocalGraphicsView::sendMakerNumber(QVector<QVector<int>> * _t1, QVector<QVector<int>> * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void LocalGraphicsView::sendPenType(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void LocalGraphicsView::signal_SendCurrentRectItem(QGraphicsItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void LocalGraphicsView::signal_SendCheckedState(GraphicsRectItem * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void LocalGraphicsView::sendShapeNumberMap(const QMap<QGraphicsEllipseItem*,int> & _t1, const QMap<QGraphicsPathItem*,int> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void LocalGraphicsView::sendSelectedShape(const QMap<QGraphicsEllipseItem*,int> & _t1, const QMap<QGraphicsPathItem*,int> & _t2, QGraphicsItem * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void LocalGraphicsView::sendPolygon(QGraphicsPathItem * _t1, const QPoint & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void LocalGraphicsView::sendCircle(QGraphicsEllipseItem * _t1, const QPoint & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void LocalGraphicsView::sendLocalPolygon(const QVector<QPointF> & _t1, QGraphicsPathItem * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
