cmake_minimum_required(VERSION 3.8)

project(qcalc)

foreach(p CMP0071)
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

enable_testing()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(MPIR 2.0.0 REQUIRED)
find_package(MPFR 2.3.1 REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

QT5_WRAP_UI(mainwindow_form_hdr ${CMAKE_SOURCE_DIR}/src/mainwindow.ui)
QT5_WRAP_CPP(mainwindow_hdr_moc ${CMAKE_SOURCE_DIR}/include/mainwindow.h)

QT5_WRAP_CPP(header_moc ${CMAKE_SOURCE_DIR}/include/filters.h
                        ${CMAKE_SOURCE_DIR}/include/buttons.h
                        ${CMAKE_SOURCE_DIR}/include/display.h
                        ${CMAKE_SOURCE_DIR}/include/titlebar.h
                        ${CMAKE_SOURCE_DIR}/include/basic_mode.h)

add_library(mainwindow ${CMAKE_SOURCE_DIR}/src/mainwindow.cpp
                       ${mainwindow_hdr_moc}
                       ${mainwindow_form_hdr}
                       ${header_moc})

qt5_use_modules(mainwindow Widgets)

include(${CMAKE_SOURCE_DIR}/cmake/Externals/googletest.cmake)

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${MPFR_INCLUDE_DIRS} ${MPIR_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(test)
