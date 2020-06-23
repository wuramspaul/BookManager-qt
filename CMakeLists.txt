cmake_minimum_required(VERSION 3.5)

project(paper-cerberus-old LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(paper-cerberus
    main.cpp

    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    papercerberus.cpp
    papercerberus.h

    newitemdialog.cpp
    newitemdialog.h
    newitemdialog.ui

    bookmodel.cpp
    bookmodel.h
)

#add_subdirectory(ziplib-cmake-master/)
target_link_libraries(paper-cerberus PRIVATE Qt5::Widgets )


