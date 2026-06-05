cmake_minimum_required(VERSION 3.16)

project(WeaponSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets Test QUIET)
set(QT_LIBRARIES Qt6::Widgets)
set(QT_TEST_LIBRARIES Qt6::Test)


set(WEAPON_LOGIC_SOURCES
    AbstractWeapon.h
    AbstractFireWeapon.h
    ColdSteel.h
    Pistol.h
    Rifle.h
    WeaponFactory.h
    ColdSteelFactory.h
    PistolFactory.h
    RifleFactory.h
    MilitaryUnit.h
)

add_executable(WeaponQtApp
    main.cpp
    mainwindow.h
    mainwindow.cpp
    AddEditForm.h
    AddEditForm.cpp
    mainwindow.ui
    ${WEAPON_LOGIC_SOURCES}
)
target_link_libraries(WeaponQtApp PRIVATE ${QT_LIBRARIES})

add_executable(WeaponTests
    testsWeapon.cpp
    ${WEAPON_LOGIC_SOURCES}
)
target_link_libraries(WeaponTests PRIVATE ${QT_LIBRARIES} ${QT_TEST_LIBRARIES})