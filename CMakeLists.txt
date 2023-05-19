cmake_minimum_required(VERSION 3.17)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(VTEg VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Change this path to your local QT cmake path
set(CMAKE_PREFIX_PATH "/Users/tommetz/Qt/6.5.0/macos/lib/cmake")

include(BreezeThemes.cmake)

#Change this path to your local OpenCV path
set(OpenCV_DIR "/Users/tommetz/opencv-4.5.0/build/include")

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui Multimedia MultimediaWidgets LinguistTools)
find_package(OpenCV REQUIRED)

#Change this path to the bin folder of your OpenCV build, if its not in PATH
file(COPY "/Users/tommetz/opencv-4.5.0/build/bin/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")

#copys the images folder into the buildfolder
file(COPY "images/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/images")

file(COPY "OD/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/OD")

include_directories(libraries ${OpenCV_INCLUDE_DIRS})

set(PROJECT_SOURCES
        main.cpp
        Windows/mainwindow.cpp Windows/mainwindow.h Windows/mainwindow.ui ui/ui_mainwindow.h
        Utilities/VideoTag.cpp Utilities/VideoTag.h
        Windows/videowidget.cpp Windows/videowidget.h
        Windows/videowidgetsurface.cpp Windows/videowidgetsurface.h
        Windows/TagManager.cpp Windows/TagManager.h
        Utilities/VideoTagCategory.cpp Utilities/VideoTagCategory.h
        libraries/csv.h
        Utilities/CustomVideoSlider.h Utilities/CustomVideoSlider.cpp
        Utilities/VideoPreview.cpp Utilities/VideoPreview.h
        Windows/SettingsWidget.cpp Windows/SettingsWidget.h
        Utilities/Settings.cpp Utilities/Settings.h
        Utilities/HotKeyManager.h
        Utilities/FrameGrabber.cpp Utilities/FrameGrabber.h
        Utilities/ObjectDetector.cpp Utilities/ObjectDetector.h
        Utilities/TensorflowObjectDetection.cpp Utilities/TensorflowObjectDetection.h)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(VTEg MACOSX_BUNDLE
            ${PROJECT_SOURCES}
    )
    set_target_properties(VTEg PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            )
elseif(WIN32)
    add_executable(VTEg WIN32
        ${PROJECT_SOURCES}
    )
    #this will move the necessary compiler DLL files to the applications path, if this causes any problems, uncomment it and move them yourself
    if(MINGW)
        message(STATUS "Installing system-libraries: MinGW DLLs.")
        get_filename_component(Mingw_Path ${CMAKE_CXX_COMPILER} PATH)
        file(COPY "${Mingw_Path}/libwinpthread-1.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
        file(COPY "${Mingw_Path}/libstdc++-6.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
        file(COPY "${Mingw_Path}/libgcc_s_seh-1.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
elseif(LINUX)
    add_executable(VTEg ${PROJECT_SOURCES})
endif()

target_link_libraries(VTEg PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets breeze_themes ${OpenCV_LIBS})

