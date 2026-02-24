/****************************************************************************
** Meta object code from reading C++ file 'ShiftViewModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../presentation/viewmodels/ShiftViewModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShiftViewModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.2. It"
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
struct qt_meta_tag_ZN14ShiftViewModelE_t {};
} // unnamed namespace

template <> constexpr inline auto ShiftViewModel::qt_create_metaobjectdata<qt_meta_tag_ZN14ShiftViewModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ShiftViewModel",
        "hasOpenShiftChanged",
        "",
        "myOpenShiftChanged",
        "openShiftsChanged",
        "lastErrorChanged",
        "shiftOpened",
        "shiftClosed",
        "setCurrentEmployeeId",
        "id",
        "refresh",
        "openShift",
        "closeMyShift",
        "closeTimeStr",
        "closeShiftForEmployee",
        "shiftId",
        "hasOpenShift",
        "myOpenShift",
        "QVariantMap",
        "openShifts",
        "QVariantList",
        "lastError"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'hasOpenShiftChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'myOpenShiftChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'openShiftsChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lastErrorChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'shiftOpened'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'shiftClosed'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setCurrentEmployeeId'
        QtMocHelpers::MethodData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Method 'refresh'
        QtMocHelpers::MethodData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'openShift'
        QtMocHelpers::MethodData<bool()>(11, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'closeMyShift'
        QtMocHelpers::MethodData<bool(const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 13 },
        }}),
        // Method 'closeShiftForEmployee'
        QtMocHelpers::MethodData<bool(const QString &, const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 15 }, { QMetaType::QString, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'hasOpenShift'
        QtMocHelpers::PropertyData<bool>(16, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'myOpenShift'
        QtMocHelpers::PropertyData<QVariantMap>(17, 0x80000000 | 18, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
        // property 'openShifts'
        QtMocHelpers::PropertyData<QVariantList>(19, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 2),
        // property 'lastError'
        QtMocHelpers::PropertyData<QString>(21, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ShiftViewModel, qt_meta_tag_ZN14ShiftViewModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ShiftViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ShiftViewModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ShiftViewModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ShiftViewModelE_t>.metaTypes,
    nullptr
} };

void ShiftViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ShiftViewModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->hasOpenShiftChanged(); break;
        case 1: _t->myOpenShiftChanged(); break;
        case 2: _t->openShiftsChanged(); break;
        case 3: _t->lastErrorChanged(); break;
        case 4: _t->shiftOpened(); break;
        case 5: _t->shiftClosed(); break;
        case 6: _t->setCurrentEmployeeId((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->refresh(); break;
        case 8: { bool _r = _t->openShift();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->closeMyShift((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->closeShiftForEmployee((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ShiftViewModel::*)()>(_a, &ShiftViewModel::hasOpenShiftChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShiftViewModel::*)()>(_a, &ShiftViewModel::myOpenShiftChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShiftViewModel::*)()>(_a, &ShiftViewModel::openShiftsChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShiftViewModel::*)()>(_a, &ShiftViewModel::lastErrorChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShiftViewModel::*)()>(_a, &ShiftViewModel::shiftOpened, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ShiftViewModel::*)()>(_a, &ShiftViewModel::shiftClosed, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->hasOpenShift(); break;
        case 1: *reinterpret_cast<QVariantMap*>(_v) = _t->myOpenShift(); break;
        case 2: *reinterpret_cast<QVariantList*>(_v) = _t->openShifts(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->lastError(); break;
        default: break;
        }
    }
}

const QMetaObject *ShiftViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShiftViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ShiftViewModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ShiftViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ShiftViewModel::hasOpenShiftChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ShiftViewModel::myOpenShiftChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ShiftViewModel::openShiftsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ShiftViewModel::lastErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ShiftViewModel::shiftOpened()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ShiftViewModel::shiftClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
