/****************************************************************************
** Meta object code from reading C++ file 'particleswarmoptimization.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "particleswarmoptimization.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'particleswarmoptimization.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParticleSwarmOptimization_t {
    QByteArrayData data[23];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParticleSwarmOptimization_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParticleSwarmOptimization_t qt_meta_stringdata_ParticleSwarmOptimization = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ParticleSwarmOptimization"
QT_MOC_LITERAL(1, 26, 17), // "problema_generado"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 16), // "vector<structxy>"
QT_MOC_LITERAL(4, 62, 10), // "obstaculos"
QT_MOC_LITERAL(5, 73, 21), // "vector<strucparticle>"
QT_MOC_LITERAL(6, 95, 10), // "particulas"
QT_MOC_LITERAL(7, 106, 8), // "structxy"
QT_MOC_LITERAL(8, 115, 6), // "inicio"
QT_MOC_LITERAL(9, 122, 18), // "vector<structidxy>"
QT_MOC_LITERAL(10, 141, 3), // "fin"
QT_MOC_LITERAL(11, 145, 10), // "structMapa"
QT_MOC_LITERAL(12, 156, 9), // "XYLimMapa"
QT_MOC_LITERAL(13, 166, 16), // "CurrentIteration"
QT_MOC_LITERAL(14, 183, 17), // "objeto_encontrado"
QT_MOC_LITERAL(15, 201, 4), // "vect"
QT_MOC_LITERAL(16, 206, 21), // "send_request_particle"
QT_MOC_LITERAL(17, 228, 2), // "id"
QT_MOC_LITERAL(18, 231, 8), // "enjambre"
QT_MOC_LITERAL(19, 240, 21), // "send_command_particle"
QT_MOC_LITERAL(20, 262, 2), // "vx"
QT_MOC_LITERAL(21, 265, 2), // "vy"
QT_MOC_LITERAL(22, 268, 1) // "t"

    },
    "ParticleSwarmOptimization\0problema_generado\0"
    "\0vector<structxy>\0obstaculos\0"
    "vector<strucparticle>\0particulas\0"
    "structxy\0inicio\0vector<structidxy>\0"
    "fin\0structMapa\0XYLimMapa\0CurrentIteration\0"
    "objeto_encontrado\0vect\0send_request_particle\0"
    "id\0enjambre\0send_command_particle\0vx\0"
    "vy\0t"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParticleSwarmOptimization[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,   34,    2, 0x06 /* Public */,
      14,    1,   47,    2, 0x06 /* Public */,
      16,    2,   50,    2, 0x06 /* Public */,
      19,    4,   55,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11, QMetaType::UInt,    4,    6,    8,   10,   12,   13,
    QMetaType::Void, 0x80000000 | 7,   15,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,   17,   18,
    QMetaType::Void, QMetaType::UInt, QMetaType::Double, QMetaType::Double, QMetaType::Double,   17,   20,   21,   22,

       0        // eod
};

void ParticleSwarmOptimization::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParticleSwarmOptimization *_t = static_cast<ParticleSwarmOptimization *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->problema_generado((*reinterpret_cast< vector<structxy>(*)>(_a[1])),(*reinterpret_cast< vector<strucparticle>(*)>(_a[2])),(*reinterpret_cast< structxy(*)>(_a[3])),(*reinterpret_cast< vector<structidxy>(*)>(_a[4])),(*reinterpret_cast< structMapa(*)>(_a[5])),(*reinterpret_cast< uint(*)>(_a[6]))); break;
        case 1: _t->objeto_encontrado((*reinterpret_cast< structxy(*)>(_a[1]))); break;
        case 2: _t->send_request_particle((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->send_command_particle((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ParticleSwarmOptimization::*_t)(vector<structxy> , vector<strucparticle> , structxy , vector<structidxy> , structMapa , unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParticleSwarmOptimization::problema_generado)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ParticleSwarmOptimization::*_t)(structxy );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParticleSwarmOptimization::objeto_encontrado)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ParticleSwarmOptimization::*_t)(unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParticleSwarmOptimization::send_request_particle)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ParticleSwarmOptimization::*_t)(unsigned int , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParticleSwarmOptimization::send_command_particle)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ParticleSwarmOptimization::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ParticleSwarmOptimization.data,
      qt_meta_data_ParticleSwarmOptimization,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ParticleSwarmOptimization::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParticleSwarmOptimization::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ParticleSwarmOptimization.stringdata0))
        return static_cast<void*>(const_cast< ParticleSwarmOptimization*>(this));
    return QThread::qt_metacast(_clname);
}

int ParticleSwarmOptimization::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ParticleSwarmOptimization::problema_generado(vector<structxy> _t1, vector<strucparticle> _t2, structxy _t3, vector<structidxy> _t4, structMapa _t5, unsigned int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ParticleSwarmOptimization::objeto_encontrado(structxy _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ParticleSwarmOptimization::send_request_particle(unsigned int _t1, unsigned int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ParticleSwarmOptimization::send_command_particle(unsigned int _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
