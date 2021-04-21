cmake_minimum_required(VERSION 3.14)

project(prt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_MACOSX_BUNDLE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
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
        quizsettingsmodel.cpp
        quizsetting.cpp
)

qt_add_resources(PROJECT_SOURCES qml.qrc)

qt_add_executable(prt
  ${PROJECT_SOURCES}
)

add_subdirectory(prc)

target_compile_definitions(prt
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(prt
  PRIVATE
  Qt6::Core
  Qt6::Quick
  Qt6::quickwindow
  Qt6::qtquick2plugin
  Qt6::qtquickcontrols2plugin
  Qt6::qtquickcontrols2macosstyleplugin
  Qt6::qtquickcontrols2fusionstyleplugin
  Qt6::qtquickcontrols2basicstyleplugin
  Qt6::qtquickcontrols2nativestyleplugin
  Qt6::qtquickcontrols2implplugin
  Qt6::qquicklayoutsplugin
  Qt6::qtquicktemplates2plugin
  Qt6::qtlabsplatformplugin
  Qt6::qtquickcontrols2fusionstyleimplplugin
  Qt6::qmlplugin
  Qt6::modelsplugin
  Qt6::workerscriptplugin
  libprc
)

install(TARGETS prt
  EXPORT prt
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  BUNDLE DESTINATION bin
)
