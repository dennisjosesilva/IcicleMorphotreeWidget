project(IcecleMorphotreeWidget)

cmake_minimum_required(VERSION 3.10)

include_directories(include appTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QT CONFIG
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

# CONAN CONFIG
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# SOURCES
file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# APP TEST
set(APP_TEST_SOURCE 
   appTest/RenderingPanel/CustomWidgets/UnitSliderWidget.cpp
   appTest/RenderingPanel/FlatRenderingWidget.cpp
   appTest/RenderingPanel/HGradientRenderingWidget.cpp
   appTest/RenderingPanel/GeoShaderRenderingWidget.cpp
   appTest/RenderingPanel/TessShaderRenderingWidget.cpp
   appTest/RenderingPanel/NodeRenderingWidget.cpp
   appTest/RenderingPanel/RenderingPanel.cpp
   appTest/main.cpp 
   appTest/mainwindow.cpp)

# MOC SOURCE
qt5_wrap_cpp(PROJECT_SOURCE
   appTest/RenderingPanel/CustomWidgets/UnitSliderWidget.hpp
   appTest/RenderingPanel/GeoShaderRenderingWidget.hpp
   appTest/RenderingPanel/TessShaderRenderingWidget.hpp
   include/IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp
   include/IcicleMorphotreeWidget/Graphics/Node/GNodeEventHandler.hpp
   include/IcicleMorphotreeWidget/Graphics/ColorBar.hpp)

qt5_wrap_cpp(APP_TEST_SOURCE
   appTest/mainwindow.hpp)

# SET RESOURCE FILES
qt5_add_resources(PROJECT_SOURCE IcicleMorphotreeWidgetResource.qrc)

# LIB
add_library(IcecleMorphotreeWidgetLib ${PROJECT_SOURCE})
target_link_libraries(IcecleMorphotreeWidgetLib PUBLIC ${CONAN_LIBS} Qt5::Widgets Qt5::Core Qt5::Gui)

# EXECUTABLES
add_executable(appTest ${APP_TEST_SOURCE})
target_link_libraries(appTest PUBLIC 
  IcecleMorphotreeWidgetLib
  ${CONAN_LIBS}
  Qt5::Core Qt5::Gui Qt5::Widgets)