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
set(APP_TEST_SOURCE appTest/main.cpp appTest/mainwindow.cpp)

# MOC SOURCE
qt5_wrap_cpp(PROJECT_SOURCE
   include/IcicleMorphotreeWidget/Graphics/GNodeEventHandler.hpp)

qt5_wrap_cpp(APP_TEST_SOURCE
   appTest/mainwindow.hpp)

# LIB
add_library(IcecleMorphotreeWidgetLib ${PROJECT_SOURCE})
target_link_libraries(IcecleMorphotreeWidgetLib PUBLIC ${CONAN_LIBS} Qt5::Widgets Qt5::Core Qt5::Gui)

# EXECUTABLES
add_executable(appTest ${APP_TEST_SOURCE})
target_link_libraries(appTest PUBLIC 
  IcecleMorphotreeWidgetLib
  ${CONAN_LIBS}
  Qt5::Core Qt5::Gui Qt5::Widgets)