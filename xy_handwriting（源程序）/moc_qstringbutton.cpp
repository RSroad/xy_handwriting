/****************************************************************************
** Meta object code from reading C++ file 'qstringbutton.h'
**
** Created: Thu Nov 24 13:10:02 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qstringbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qstringbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QStringButton[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QStringButton[] = {
    "QStringButton\0\0click_with_string(QString)\0"
    "emit_string_signal()\0"
};

const QMetaObject QStringButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_QStringButton,
      qt_meta_data_QStringButton, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QStringButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QStringButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QStringButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QStringButton))
        return static_cast<void*>(const_cast< QStringButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int QStringButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: click_with_string((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: emit_string_signal(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QStringButton::click_with_string(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
