cmake_minimum_required(VERSION 3.14)

project(prt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt6 COMPONENTS Core Quick Concurrent REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        rangeloader.cpp
        qml.qrc
        treeviewmodel.cpp
        range.cpp
        rangedisplayer.cpp
        handinfo.cpp
        rangeinfo.cpp
        quizer.cpp
        quizchoice.cpp
)

qt_add_executable(prt
  ${PROJECT_SOURCES}
)

add_subdirectory(prc)

target_compile_definitions(prt
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(prt
  PRIVATE Qt6::Core Qt6::Quick libprc)
