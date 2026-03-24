/****************************************************************************
** Meta object code from reading C++ file 'FinanceViewModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../presentation/viewmodels/FinanceViewModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FinanceViewModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16FinanceViewModelE_t {};
} // unnamed namespace

template <> constexpr inline auto FinanceViewModel::qt_create_metaobjectdata<qt_meta_tag_ZN16FinanceViewModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FinanceViewModel",
        "totalsChanged",
        "",
        "transactionsChanged",
        "lastErrorChanged",
        "waiterAggregatesChanged",
        "reload",
        "addIncome",
        "amountRubles",
        "category",
        "description",
        "addExpense",
        "updateTransaction",
        "id",
        "type",
        "deleteTransaction",
        "formatMoney",
        "rubles",
        "totalIncome",
        "totalExpenses",
        "profit",
        "transactions",
        "QVariantList",
        "incomeTransactions",
        "expenseTransactions",
        "lastError",
        "waiterAggregates"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'totalsChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'transactionsChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lastErrorChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'waiterAggregatesChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'reload'
        QtMocHelpers::MethodData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'addIncome'
        QtMocHelpers::MethodData<bool(double, const QString &, const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Double, 8 }, { QMetaType::QString, 9 }, { QMetaType::QString, 10 },
        }}),
        // Method 'addIncome'
        QtMocHelpers::MethodData<bool(double, const QString &)>(7, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool, {{
            { QMetaType::Double, 8 }, { QMetaType::QString, 9 },
        }}),
        // Method 'addExpense'
        QtMocHelpers::MethodData<bool(double, const QString &, const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Double, 8 }, { QMetaType::QString, 9 }, { QMetaType::QString, 10 },
        }}),
        // Method 'addExpense'
        QtMocHelpers::MethodData<bool(double, const QString &)>(11, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool, {{
            { QMetaType::Double, 8 }, { QMetaType::QString, 9 },
        }}),
        // Method 'updateTransaction'
        QtMocHelpers::MethodData<bool(int, int, double, const QString &, const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 13 }, { QMetaType::Int, 14 }, { QMetaType::Double, 8 }, { QMetaType::QString, 9 },
            { QMetaType::QString, 10 },
        }}),
        // Method 'deleteTransaction'
        QtMocHelpers::MethodData<bool(int)>(15, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 13 },
        }}),
        // Method 'formatMoney'
        QtMocHelpers::MethodData<QString(double) const>(16, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Double, 17 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'totalIncome'
        QtMocHelpers::PropertyData<double>(18, QMetaType::Double, QMC::DefaultPropertyFlags, 0),
        // property 'totalExpenses'
        QtMocHelpers::PropertyData<double>(19, QMetaType::Double, QMC::DefaultPropertyFlags, 0),
        // property 'profit'
        QtMocHelpers::PropertyData<double>(20, QMetaType::Double, QMC::DefaultPropertyFlags, 0),
        // property 'transactions'
        QtMocHelpers::PropertyData<QVariantList>(21, 0x80000000 | 22, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
        // property 'incomeTransactions'
        QtMocHelpers::PropertyData<QVariantList>(23, 0x80000000 | 22, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
        // property 'expenseTransactions'
        QtMocHelpers::PropertyData<QVariantList>(24, 0x80000000 | 22, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
        // property 'lastError'
        QtMocHelpers::PropertyData<QString>(25, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'waiterAggregates'
        QtMocHelpers::PropertyData<QVariantList>(26, 0x80000000 | 22, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 3),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<FinanceViewModel, qt_meta_tag_ZN16FinanceViewModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject FinanceViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16FinanceViewModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16FinanceViewModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16FinanceViewModelE_t>.metaTypes,
    nullptr
} };

void FinanceViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FinanceViewModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->totalsChanged(); break;
        case 1: _t->transactionsChanged(); break;
        case 2: _t->lastErrorChanged(); break;
        case 3: _t->waiterAggregatesChanged(); break;
        case 4: _t->reload(); break;
        case 5: { bool _r = _t->addIncome((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->addIncome((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->addExpense((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->addExpense((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->updateTransaction((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->deleteTransaction((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->formatMoney((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FinanceViewModel::*)()>(_a, &FinanceViewModel::totalsChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FinanceViewModel::*)()>(_a, &FinanceViewModel::transactionsChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (FinanceViewModel::*)()>(_a, &FinanceViewModel::lastErrorChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (FinanceViewModel::*)()>(_a, &FinanceViewModel::waiterAggregatesChanged, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<double*>(_v) = _t->totalIncome(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->totalExpenses(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->profit(); break;
        case 3: *reinterpret_cast<QVariantList*>(_v) = _t->transactions(); break;
        case 4: *reinterpret_cast<QVariantList*>(_v) = _t->incomeTransactions(); break;
        case 5: *reinterpret_cast<QVariantList*>(_v) = _t->expenseTransactions(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->lastError(); break;
        case 7: *reinterpret_cast<QVariantList*>(_v) = _t->waiterAggregates(); break;
        default: break;
        }
    }
}

const QMetaObject *FinanceViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FinanceViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16FinanceViewModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FinanceViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void FinanceViewModel::totalsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FinanceViewModel::transactionsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FinanceViewModel::lastErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FinanceViewModel::waiterAggregatesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
