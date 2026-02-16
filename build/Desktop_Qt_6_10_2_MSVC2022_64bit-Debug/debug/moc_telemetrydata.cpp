/****************************************************************************
** Meta object code from reading C++ file 'telemetrydata.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../telemetrydata.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'telemetrydata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13TelemetryDataE_t {};
} // unnamed namespace

template <> constexpr inline auto TelemetryData::qt_create_metaobjectdata<qt_meta_tag_ZN13TelemetryDataE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TelemetryData",
        "speedKmhChanged",
        "",
        "batteryPercentChanged",
        "reverseChanged",
        "gpsOkChanged",
        "latChanged",
        "lonChanged",
        "headingChanged",
        "alertTextChanged",
        "alertLevelChanged",
        "simulateRouteRequested",
        "QVariantList",
        "routeCoords",
        "setSpeedKmh",
        "v",
        "setBatteryPercent",
        "setReverse",
        "setGpsOk",
        "setLat",
        "setLon",
        "setHeading",
        "setAlertText",
        "setAlertLevel",
        "speedKmh",
        "batteryPercent",
        "reverse",
        "gpsOk",
        "lat",
        "lon",
        "heading",
        "alertText",
        "alertLevel"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'speedKmhChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'batteryPercentChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'reverseChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gpsOkChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'latChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lonChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'headingChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'alertTextChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'alertLevelChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'simulateRouteRequested'
        QtMocHelpers::SignalData<void(QVariantList)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Slot 'setSpeedKmh'
        QtMocHelpers::SlotData<void(double)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 15 },
        }}),
        // Slot 'setBatteryPercent'
        QtMocHelpers::SlotData<void(int)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Slot 'setReverse'
        QtMocHelpers::SlotData<void(bool)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 15 },
        }}),
        // Slot 'setGpsOk'
        QtMocHelpers::SlotData<void(bool)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 15 },
        }}),
        // Slot 'setLat'
        QtMocHelpers::SlotData<void(double)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 15 },
        }}),
        // Slot 'setLon'
        QtMocHelpers::SlotData<void(double)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 15 },
        }}),
        // Slot 'setHeading'
        QtMocHelpers::SlotData<void(double)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 15 },
        }}),
        // Slot 'setAlertText'
        QtMocHelpers::SlotData<void(const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'setAlertLevel'
        QtMocHelpers::SlotData<void(int)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'speedKmh'
        QtMocHelpers::PropertyData<double>(24, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'batteryPercent'
        QtMocHelpers::PropertyData<int>(25, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'reverse'
        QtMocHelpers::PropertyData<bool>(26, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'gpsOk'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'lat'
        QtMocHelpers::PropertyData<double>(28, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'lon'
        QtMocHelpers::PropertyData<double>(29, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'heading'
        QtMocHelpers::PropertyData<double>(30, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'alertText'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'alertLevel'
        QtMocHelpers::PropertyData<int>(32, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TelemetryData, qt_meta_tag_ZN13TelemetryDataE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TelemetryData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TelemetryDataE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TelemetryDataE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13TelemetryDataE_t>.metaTypes,
    nullptr
} };

void TelemetryData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TelemetryData *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->speedKmhChanged(); break;
        case 1: _t->batteryPercentChanged(); break;
        case 2: _t->reverseChanged(); break;
        case 3: _t->gpsOkChanged(); break;
        case 4: _t->latChanged(); break;
        case 5: _t->lonChanged(); break;
        case 6: _t->headingChanged(); break;
        case 7: _t->alertTextChanged(); break;
        case 8: _t->alertLevelChanged(); break;
        case 9: _t->simulateRouteRequested((*reinterpret_cast<std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 10: _t->setSpeedKmh((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 11: _t->setBatteryPercent((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->setReverse((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->setGpsOk((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->setLat((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 15: _t->setLon((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 16: _t->setHeading((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 17: _t->setAlertText((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->setAlertLevel((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::speedKmhChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::batteryPercentChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::reverseChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::gpsOkChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::latChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::lonChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::headingChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::alertTextChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)()>(_a, &TelemetryData::alertLevelChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (TelemetryData::*)(QVariantList )>(_a, &TelemetryData::simulateRouteRequested, 9))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<double*>(_v) = _t->speedKmh(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->batteryPercent(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->reverse(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->gpsOk(); break;
        case 4: *reinterpret_cast<double*>(_v) = _t->lat(); break;
        case 5: *reinterpret_cast<double*>(_v) = _t->lon(); break;
        case 6: *reinterpret_cast<double*>(_v) = _t->heading(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->alertText(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->alertLevel(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSpeedKmh(*reinterpret_cast<double*>(_v)); break;
        case 1: _t->setBatteryPercent(*reinterpret_cast<int*>(_v)); break;
        case 2: _t->setReverse(*reinterpret_cast<bool*>(_v)); break;
        case 3: _t->setGpsOk(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setLat(*reinterpret_cast<double*>(_v)); break;
        case 5: _t->setLon(*reinterpret_cast<double*>(_v)); break;
        case 6: _t->setHeading(*reinterpret_cast<double*>(_v)); break;
        case 7: _t->setAlertText(*reinterpret_cast<QString*>(_v)); break;
        case 8: _t->setAlertLevel(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *TelemetryData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TelemetryData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13TelemetryDataE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TelemetryData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void TelemetryData::speedKmhChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TelemetryData::batteryPercentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TelemetryData::reverseChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TelemetryData::gpsOkChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TelemetryData::latChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void TelemetryData::lonChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TelemetryData::headingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void TelemetryData::alertTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void TelemetryData::alertLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void TelemetryData::simulateRouteRequested(QVariantList _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}
QT_WARNING_POP
