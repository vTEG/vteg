cmake_minimum_required(VERSION 3.19)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(VTEg VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Change this path to your local QT cmake path
#set(CMAKE_PREFIX_PATH "C:/Qt/5.12.11/mingw73_64/lib/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.12.11\\mingw73_64\\lib\\cmake")

find_package(QT NAMES Qt5 COMPONENTS Widgets Gui Multimedia MultimediaWidgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui Multimedia MultimediaWidgets LinguistTools REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        VideoTag.cpp
        VideoTag.h
        videowidget.cpp
        videowidget.h
        videowidgetsurface.cpp
        videowidgetsurface.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VTEg
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(VTEg SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(VTEg
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(VTEg PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)

set_target_properties(VTEg PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VTEg)
endif()
