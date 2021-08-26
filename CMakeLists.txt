cmake_minimum_required(VERSION 3.17)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(VTEg VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Change this path to your local QT cmake path
#setHotkey(CMAKE_PREFIX_PATH "/Path/To/Your/Qt/Folder")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets Gui Multimedia MultimediaWidgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui Multimedia MultimediaWidgets LinguistTools REQUIRED)

#copys the images folder into the buildfolder
file(COPY "images/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/images")

set(PROJECT_SOURCES
        main.cpp
        Windows/mainwindow.cpp Windows/mainwindow.h Windows/mainwindow.ui ui/ui_mainwindow.h
        Utilities/VideoTag.cpp Utilities/VideoTag.h
        Windows/videowidget.cpp Windows/videowidget.h
        Windows/videowidgetsurface.cpp Windows/videowidgetsurface.h
        Windows/TagManager.cpp Windows/TagManager.h
        Utilities/VideoTagCategory.cpp Utilities/VideoTagCategory.h
        libraries/csv.h
        Utilities/CustomVideoSlider.h Utilities/CustomVideoSlider.cpp Utilities/VideoPreview.cpp Utilities/VideoPreview.h Windows/SettingsWidget.cpp Windows/SettingsWidget.h Utilities/Settings.cpp Utilities/Settings.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VTEg
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(VTEg SHARED
            ${PROJECT_SOURCES}
        )
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        add_executable(VTEg MACOSX_BUNDLE
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
