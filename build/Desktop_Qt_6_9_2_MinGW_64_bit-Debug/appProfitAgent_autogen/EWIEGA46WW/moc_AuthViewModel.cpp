/****************************************************************************
** Meta object code from reading C++ file 'AuthViewModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../AuthViewModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AuthViewModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13AuthViewModelE_t {};
} // unnamed namespace

template <> constexpr inline auto AuthViewModel::qt_create_metaobjectdata<qt_meta_tag_ZN13AuthViewModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AuthViewModel",
        "loginChanged",
        "",
        "passwordChanged",
        "selectedRoleChanged",
        "isAuthenticatedChanged",
        "loginSuccess",
        "role",
        "loginFailed",
        "performLogin",
        "logout",
        "login",
        "password",
        "selectedRole",
        "isAuthenticated",
        "Role",
        "Waiter",
        "Chef",
        "Manager",
        "Director"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'loginChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'passwordChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'selectedRoleChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isAuthenticatedChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'loginSuccess'
        QtMocHelpers::SignalData<void(int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Signal 'loginFailed'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'performLogin'
        QtMocHelpers::MethodData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'logout'
        QtMocHelpers::MethodData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'login'
        QtMocHelpers::PropertyData<QString>(11, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'password'
        QtMocHelpers::PropertyData<QString>(12, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'selectedRole'
        QtMocHelpers::PropertyData<int>(13, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'isAuthenticated'
        QtMocHelpers::PropertyData<bool>(14, QMetaType::Bool, QMC::DefaultPropertyFlags, 3),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Role'
        QtMocHelpers::EnumData<enum Role>(15, 15, QMC::EnumFlags{}).add({
            {   16, Role::Waiter },
            {   17, Role::Chef },
            {   18, Role::Manager },
            {   19, Role::Director },
        }),
    };
    return QtMocHelpers::metaObjectData<AuthViewModel, qt_meta_tag_ZN13AuthViewModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AuthViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AuthViewModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AuthViewModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13AuthViewModelE_t>.metaTypes,
    nullptr
} };

void AuthViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AuthViewModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->loginChanged(); break;
        case 1: _t->passwordChanged(); break;
        case 2: _t->selectedRoleChanged(); break;
        case 3: _t->isAuthenticatedChanged(); break;
        case 4: _t->loginSuccess((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->loginFailed(); break;
        case 6: _t->performLogin(); break;
        case 7: _t->logout(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AuthViewModel::*)()>(_a, &AuthViewModel::loginChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthViewModel::*)()>(_a, &AuthViewModel::passwordChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthViewModel::*)()>(_a, &AuthViewModel::selectedRoleChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthViewModel::*)()>(_a, &AuthViewModel::isAuthenticatedChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthViewModel::*)(int )>(_a, &AuthViewModel::loginSuccess, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AuthViewModel::*)()>(_a, &AuthViewModel::loginFailed, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->login(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->password(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->selectedRole(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->isAuthenticated(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLogin(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setPassword(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setSelectedRole(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *AuthViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuthViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AuthViewModelE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AuthViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
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
void AuthViewModel::loginChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AuthViewModel::passwordChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AuthViewModel::selectedRoleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AuthViewModel::isAuthenticatedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AuthViewModel::loginSuccess(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void AuthViewModel::loginFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
