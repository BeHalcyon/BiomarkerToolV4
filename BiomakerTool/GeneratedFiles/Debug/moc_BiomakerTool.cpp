/****************************************************************************
** Meta object code from reading C++ file 'BiomakerTool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BiomakerTool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BiomakerTool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BiomakerTool_t {
    QByteArrayData data[14];
    char stringdata0[295];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BiomakerTool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BiomakerTool_t qt_meta_stringdata_BiomakerTool = {
    {
QT_MOC_LITERAL(0, 0, 12), // "BiomakerTool"
QT_MOC_LITERAL(1, 13, 26), // "on_slotOpenImage_triggered"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 27), // "on_slotExportMark_triggered"
QT_MOC_LITERAL(4, 69, 26), // "on_slotExportNav_triggered"
QT_MOC_LITERAL(5, 96, 28), // "on_slotExportPaths_triggered"
QT_MOC_LITERAL(6, 125, 27), // "on_slotImportMark_triggered"
QT_MOC_LITERAL(7, 153, 28), // "on_slotImportPaths_triggered"
QT_MOC_LITERAL(8, 182, 26), // "on_slotImportNav_triggered"
QT_MOC_LITERAL(9, 209, 12), // "setShowImage"
QT_MOC_LITERAL(10, 222, 25), // "setNavigationChoosedImage"
QT_MOC_LITERAL(11, 248, 9), // "writeFile"
QT_MOC_LITERAL(12, 258, 27), // "QVector<GraphicsRectItem*>&"
QT_MOC_LITERAL(13, 286, 8) // "filename"

    },
    "BiomakerTool\0on_slotOpenImage_triggered\0"
    "\0on_slotExportMark_triggered\0"
    "on_slotExportNav_triggered\0"
    "on_slotExportPaths_triggered\0"
    "on_slotImportMark_triggered\0"
    "on_slotImportPaths_triggered\0"
    "on_slotImportNav_triggered\0setShowImage\0"
    "setNavigationChoosedImage\0writeFile\0"
    "QVector<GraphicsRectItem*>&\0filename"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BiomakerTool[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    1,   71,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      11,    2,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF,    2,
    QMetaType::Void, QMetaType::QPointF,    2,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString,    2,   13,

       0        // eod
};

void BiomakerTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BiomakerTool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_slotOpenImage_triggered(); break;
        case 1: _t->on_slotExportMark_triggered(); break;
        case 2: _t->on_slotExportNav_triggered(); break;
        case 3: _t->on_slotExportPaths_triggered(); break;
        case 4: _t->on_slotImportMark_triggered(); break;
        case 5: _t->on_slotImportPaths_triggered(); break;
        case 6: _t->on_slotImportNav_triggered(); break;
        case 7: _t->setShowImage((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 8: _t->setNavigationChoosedImage((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 9: _t->writeFile((*reinterpret_cast< QVector<GraphicsRectItem*>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BiomakerTool::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_BiomakerTool.data,
    qt_meta_data_BiomakerTool,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BiomakerTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BiomakerTool::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BiomakerTool.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int BiomakerTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
