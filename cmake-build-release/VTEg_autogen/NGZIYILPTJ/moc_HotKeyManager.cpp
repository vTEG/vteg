/****************************************************************************
** Meta object code from reading C++ file 'HotKeyManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Utilities/HotKeyManager.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HotKeyManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS = QtMocHelpers::stringData(
    "HotKeyActionWrapper",
    "HotKeyAction",
    "NO_ACTION",
    "OPEN_FILE",
    "CLOSE_FILE",
    "SAVE_FILE",
    "SAVE_FILE_AS",
    "ADD_TAG",
    "REMOVE_TAG",
    "EDIT_TAG"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[20];
    char stringdata1[13];
    char stringdata2[10];
    char stringdata3[10];
    char stringdata4[11];
    char stringdata5[10];
    char stringdata6[13];
    char stringdata7[8];
    char stringdata8[11];
    char stringdata9[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS_t qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS = {
    {
        QT_MOC_LITERAL(0, 19),  // "HotKeyActionWrapper"
        QT_MOC_LITERAL(20, 12),  // "HotKeyAction"
        QT_MOC_LITERAL(33, 9),  // "NO_ACTION"
        QT_MOC_LITERAL(43, 9),  // "OPEN_FILE"
        QT_MOC_LITERAL(53, 10),  // "CLOSE_FILE"
        QT_MOC_LITERAL(64, 9),  // "SAVE_FILE"
        QT_MOC_LITERAL(74, 12),  // "SAVE_FILE_AS"
        QT_MOC_LITERAL(87, 7),  // "ADD_TAG"
        QT_MOC_LITERAL(95, 10),  // "REMOVE_TAG"
        QT_MOC_LITERAL(106, 8)   // "EDIT_TAG"
    },
    "HotKeyActionWrapper",
    "HotKeyAction",
    "NO_ACTION",
    "OPEN_FILE",
    "CLOSE_FILE",
    "SAVE_FILE",
    "SAVE_FILE_AS",
    "ADD_TAG",
    "REMOVE_TAG",
    "EDIT_TAG"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSHotKeyActionWrapperENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    8,   19,

 // enum data: key, value
       2, uint(HotKeyActionWrapper::NO_ACTION),
       3, uint(HotKeyActionWrapper::OPEN_FILE),
       4, uint(HotKeyActionWrapper::CLOSE_FILE),
       5, uint(HotKeyActionWrapper::SAVE_FILE),
       6, uint(HotKeyActionWrapper::SAVE_FILE_AS),
       7, uint(HotKeyActionWrapper::ADD_TAG),
       8, uint(HotKeyActionWrapper::REMOVE_TAG),
       9, uint(HotKeyActionWrapper::EDIT_TAG),

       0        // eod
};

Q_CONSTINIT const QMetaObject HotKeyActionWrapper::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSHotKeyActionWrapperENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<HotKeyActionWrapper, std::true_type>
    >,
    nullptr
} };

void HotKeyActionWrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *HotKeyActionWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HotKeyActionWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSHotKeyActionWrapperENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HotKeyActionWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSHotKeyManagerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSHotKeyManagerENDCLASS = QtMocHelpers::stringData(
    "HotKeyManager"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSHotKeyManagerENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSHotKeyManagerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSHotKeyManagerENDCLASS_t qt_meta_stringdata_CLASSHotKeyManagerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13)   // "HotKeyManager"
    },
    "HotKeyManager"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSHotKeyManagerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject HotKeyManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSHotKeyManagerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSHotKeyManagerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSHotKeyManagerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<HotKeyManager, std::true_type>
    >,
    nullptr
} };

void HotKeyManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *HotKeyManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HotKeyManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSHotKeyManagerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HotKeyManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
