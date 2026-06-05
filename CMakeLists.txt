cmake_minimum_required(VERSION 3.16)

project(WeaponSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую генерацию мета-информации Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Поиск пакета Qt (Скрипт поддерживает как Qt6, так и Qt5)
find_package(Qt6 COMPONENTS Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIBRARIES Qt5::Widgets)
else()
    set(QT_LIBRARIES Qt6::Widgets)
endif()

add_executable(WeaponQtApp
    main.cpp
    mainwindow.h
    mainwindow.cpp
    AddEditForm.h
    AddEditForm.cpp
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
    mainwindow.ui
)

# Линкуем модули Qt к нашему исполняемому файлу
target_link_libraries(WeaponQtApp PRIVATE ${QT_LIBRARIES})