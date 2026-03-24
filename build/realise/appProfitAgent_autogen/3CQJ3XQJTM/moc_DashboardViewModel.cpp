/****************************************************************************
** Meta object code from reading C++ file 'DashboardViewModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../presentation/viewmodels/DashboardViewModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DashboardViewModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15OperationsModelE_t {};
} // unnamed namespace

template <> constexpr inline auto OperationsModel::qt_create_metaobjectdata<qt_meta_tag_ZN15OperationsModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "OperationsModel"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<OperationsModel, qt_meta_tag_ZN15OperationsModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject OperationsModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15OperationsModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15OperationsModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15OperationsModelE_t>.metaTypes,
    nullptr
} };

void OperationsModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<OperationsModel *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *OperationsModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OperationsModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15OperationsModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int OperationsModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN18DashboardViewModelE_t {};
} // unnamed namespace

template <> constexpr inline auto DashboardViewModel::qt_create_metaobjectdata<qt_meta_tag_ZN18DashboardViewModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DashboardViewModel",
        "currentPageChanged",
        "",
        "totalPagesChanged",
        "userNameChanged",
        "revenueChanged",
        "revenueChangeChanged",
        "netProfitChanged",
        "netProfitChangeChanged",
        "salesCountChanged",
        "salesCountChangeChanged",
        "filterIndexChanged",
        "setCurrentPage",
        "page",
        "setUserName",
        "name",
        "reload",
        "setFilterIndex",
        "index",
        "logUiEvent",
        "eventType",
        "title",
        "details",
        "amountRubles",
        "userName",
        "revenue",
        "revenueChange",
        "netProfit",
        "netProfitChange",
        "salesCount",
        "salesCountChange",
        "operationsModel",
        "OperationsModel*",
        "currentPage",
        "totalPages",
        "filterIndex"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'currentPageChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'totalPagesChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'userNameChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'revenueChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'revenueChangeChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'netProfitChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'netProfitChangeChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'salesCountChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'salesCountChangeChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filterIndexChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setCurrentPage'
        QtMocHelpers::MethodData<void(int)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Method 'setUserName'
        QtMocHelpers::MethodData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Method 'reload'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setFilterIndex'
        QtMocHelpers::MethodData<void(int)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 18 },
        }}),
        // Method 'logUiEvent'
        QtMocHelpers::MethodData<void(const QString &, const QString &, const QString &, double)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 20 }, { QMetaType::QString, 21 }, { QMetaType::QString, 22 }, { QMetaType::Double, 23 },
        }}),
        // Method 'logUiEvent'
        QtMocHelpers::MethodData<void(const QString &, const QString &, const QString &)>(19, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 20 }, { QMetaType::QString, 21 }, { QMetaType::QString, 22 },
        }}),
        // Method 'logUiEvent'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(19, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 20 }, { QMetaType::QString, 21 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'userName'
        QtMocHelpers::PropertyData<QString>(24, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'revenue'
        QtMocHelpers::PropertyData<QString>(25, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'revenueChange'
        QtMocHelpers::PropertyData<QString>(26, QMetaType::QString, QMC::DefaultPropertyFlags, 4),
        // property 'netProfit'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'netProfitChange'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags, 6),
        // property 'salesCount'
        QtMocHelpers::PropertyData<QString>(29, QMetaType::QString, QMC::DefaultPropertyFlags, 7),
        // property 'salesCountChange'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
        // property 'operationsModel'
        QtMocHelpers::PropertyData<OperationsModel*>(31, 0x80000000 | 32, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'currentPage'
        QtMocHelpers::PropertyData<int>(33, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'totalPages'
        QtMocHelpers::PropertyData<int>(34, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'filterIndex'
        QtMocHelpers::PropertyData<int>(35, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DashboardViewModel, qt_meta_tag_ZN18DashboardViewModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DashboardViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18DashboardViewModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18DashboardViewModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18DashboardViewModelE_t>.metaTypes,
    nullptr
} };

void DashboardViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DashboardViewModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->currentPageChanged(); break;
        case 1: _t->totalPagesChanged(); break;
        case 2: _t->userNameChanged(); break;
        case 3: _t->revenueChanged(); break;
        case 4: _t->revenueChangeChanged(); break;
        case 5: _t->netProfitChanged(); break;
        case 6: _t->netProfitChangeChanged(); break;
        case 7: _t->salesCountChanged(); break;
        case 8: _t->salesCountChangeChanged(); break;
        case 9: _t->filterIndexChanged(); break;
        case 10: _t->setCurrentPage((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->setUserName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->reload(); break;
        case 13: _t->setFilterIndex((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->logUiEvent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4]))); break;
        case 15: _t->logUiEvent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 16: _t->logUiEvent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::currentPageChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::totalPagesChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::userNameChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::revenueChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::revenueChangeChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::netProfitChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::netProfitChangeChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::salesCountChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::salesCountChangeChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (DashboardViewModel::*)()>(_a, &DashboardViewModel::filterIndexChanged, 9))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< OperationsModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->userName(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->revenue(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->revenueChange(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->netProfit(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->netProfitChange(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->salesCount(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->salesCountChange(); break;
        case 7: *reinterpret_cast<OperationsModel**>(_v) = _t->operationsModel(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->currentPage(); break;
        case 9: *reinterpret_cast<int*>(_v) = _t->totalPages(); break;
        case 10: *reinterpret_cast<int*>(_v) = _t->filterIndex(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 10: _t->setFilterIndex(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DashboardViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DashboardViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18DashboardViewModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DashboardViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DashboardViewModel::currentPageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DashboardViewModel::totalPagesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DashboardViewModel::userNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DashboardViewModel::revenueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DashboardViewModel::revenueChangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void DashboardViewModel::netProfitChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void DashboardViewModel::netProfitChangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void DashboardViewModel::salesCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void DashboardViewModel::salesCountChangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void DashboardViewModel::filterIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
