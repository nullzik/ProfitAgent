/****************************************************************************
** Meta object code from reading C++ file 'WaiterViewModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../presentation/viewmodels/WaiterViewModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WaiterViewModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15WaiterViewModelE_t {};
} // unnamed namespace

template <> constexpr inline auto WaiterViewModel::qt_create_metaobjectdata<qt_meta_tag_ZN15WaiterViewModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WaiterViewModel",
        "selectedTableIdChanged",
        "",
        "isOrderDialogOpenChanged",
        "orderMessageChanged",
        "orderPlacedSuccess",
        "orderPlacedFailed",
        "reason",
        "onTableSelected",
        "tableId",
        "openOrderEntry",
        "closeOrderEntry",
        "placeOrder",
        "QVariantList",
        "orderItems",
        "selectedTableId",
        "isOrderDialogOpen",
        "orderMessage"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'selectedTableIdChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isOrderDialogOpenChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'orderMessageChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'orderPlacedSuccess'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'orderPlacedFailed'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'onTableSelected'
        QtMocHelpers::MethodData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Method 'openOrderEntry'
        QtMocHelpers::MethodData<void(int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Method 'closeOrderEntry'
        QtMocHelpers::MethodData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'placeOrder'
        QtMocHelpers::MethodData<bool(const QVariantList &)>(12, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 13, 14 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'selectedTableId'
        QtMocHelpers::PropertyData<int>(15, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'isOrderDialogOpen'
        QtMocHelpers::PropertyData<bool>(16, QMetaType::Bool, QMC::DefaultPropertyFlags, 1),
        // property 'orderMessage'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WaiterViewModel, qt_meta_tag_ZN15WaiterViewModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WaiterViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15WaiterViewModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15WaiterViewModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15WaiterViewModelE_t>.metaTypes,
    nullptr
} };

void WaiterViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WaiterViewModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->selectedTableIdChanged(); break;
        case 1: _t->isOrderDialogOpenChanged(); break;
        case 2: _t->orderMessageChanged(); break;
        case 3: _t->orderPlacedSuccess(); break;
        case 4: _t->orderPlacedFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onTableSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->openOrderEntry((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->closeOrderEntry(); break;
        case 8: { bool _r = _t->placeOrder((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WaiterViewModel::*)()>(_a, &WaiterViewModel::selectedTableIdChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (WaiterViewModel::*)()>(_a, &WaiterViewModel::isOrderDialogOpenChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (WaiterViewModel::*)()>(_a, &WaiterViewModel::orderMessageChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (WaiterViewModel::*)()>(_a, &WaiterViewModel::orderPlacedSuccess, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (WaiterViewModel::*)(const QString & )>(_a, &WaiterViewModel::orderPlacedFailed, 4))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->selectedTableId(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->isOrderDialogOpen(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->orderMessage(); break;
        default: break;
        }
    }
}

const QMetaObject *WaiterViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WaiterViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15WaiterViewModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WaiterViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WaiterViewModel::selectedTableIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WaiterViewModel::isOrderDialogOpenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WaiterViewModel::orderMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WaiterViewModel::orderPlacedSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void WaiterViewModel::orderPlacedFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
