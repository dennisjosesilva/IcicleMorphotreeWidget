project(IcicleMorphotreeWidget)

cmake_minimum_required(VERSION 3.10)

include_directories(../include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QT CONFIG
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

# CONAN CONFIG
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# SOURCES
file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# MOC SOURCE
qt5_wrap_cpp(PROJECT_SOURCE
   ../include/IcicleMorphotreeWidget/Graphics/GNodeEventHandler.hpp
   ../include/IcicleMorphotreeWidget/Graphics/ColorBar.hpp)

# LIB
add_library(IcicleMorphotreeWidget ${PROJECT_SOURCE})
target_link_libraries(IcicleMorphotreeWidget PUBLIC ${CONAN_LIBS} Qt5::Widgets Qt5::Core Qt5::Gui)