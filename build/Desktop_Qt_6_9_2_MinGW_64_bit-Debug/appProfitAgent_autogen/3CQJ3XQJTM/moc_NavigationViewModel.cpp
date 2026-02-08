/****************************************************************************
** Meta object code from reading C++ file 'NavigationViewModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../presentation/viewmodels/NavigationViewModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NavigationViewModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN19NavigationViewModelE_t {};
} // unnamed namespace

template <> constexpr inline auto NavigationViewModel::qt_create_metaobjectdata<qt_meta_tag_ZN19NavigationViewModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NavigationViewModel",
        "activeMenuItemChanged",
        "",
        "index",
        "currentSectionChanged",
        "userNameChanged",
        "userRoleChanged",
        "setActiveMenuItem",
        "setCurrentSection",
        "section",
        "setCurrentUser",
        "login",
        "role",
        "userName",
        "userRole",
        "avatarUrl",
        "activeMenuItem",
        "currentSection",
        "Section",
        "Dashboard",
        "Warehouse",
        "Menu",
        "Employees",
        "Finance",
        "Help"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'activeMenuItemChanged'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'currentSectionChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'userNameChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'userRoleChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setActiveMenuItem'
        QtMocHelpers::MethodData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Method 'setCurrentSection'
        QtMocHelpers::MethodData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Method 'setCurrentUser'
        QtMocHelpers::MethodData<void(const QString &, int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::Int, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'userName'
        QtMocHelpers::PropertyData<QString>(13, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'userRole'
        QtMocHelpers::PropertyData<QString>(14, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'avatarUrl'
        QtMocHelpers::PropertyData<QString>(15, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'activeMenuItem'
        QtMocHelpers::PropertyData<int>(16, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'currentSection'
        QtMocHelpers::PropertyData<int>(17, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Section'
        QtMocHelpers::EnumData<enum Section>(18, 18, QMC::EnumFlags{}).add({
            {   19, Section::Dashboard },
            {   20, Section::Warehouse },
            {   21, Section::Menu },
            {   22, Section::Employees },
            {   23, Section::Finance },
            {   24, Section::Help },
        }),
    };
    return QtMocHelpers::metaObjectData<NavigationViewModel, qt_meta_tag_ZN19NavigationViewModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NavigationViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NavigationViewModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NavigationViewModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19NavigationViewModelE_t>.metaTypes,
    nullptr
} };

void NavigationViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NavigationViewModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->activeMenuItemChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->currentSectionChanged(); break;
        case 2: _t->userNameChanged(); break;
        case 3: _t->userRoleChanged(); break;
        case 4: _t->setActiveMenuItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->setCurrentSection((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->setCurrentUser((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NavigationViewModel::*)(int )>(_a, &NavigationViewModel::activeMenuItemChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NavigationViewModel::*)()>(_a, &NavigationViewModel::currentSectionChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NavigationViewModel::*)()>(_a, &NavigationViewModel::userNameChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (NavigationViewModel::*)()>(_a, &NavigationViewModel::userRoleChanged, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->userName(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->userRole(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->avatarUrl(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->activeMenuItem(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->currentSection(); break;
        default: break;
        }
    }
}

const QMetaObject *NavigationViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavigationViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NavigationViewModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NavigationViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void NavigationViewModel::activeMenuItemChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void NavigationViewModel::currentSectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NavigationViewModel::userNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void NavigationViewModel::userRoleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
