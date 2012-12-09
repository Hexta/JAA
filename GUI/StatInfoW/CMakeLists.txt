cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(${project}_stw_SRC
    statInfoW.cpp
)

set(${project}_stw_HEADERS
    statInfoW.h
)

include_directories(${CMAKE_SOURCE_DIR})


QT4_WRAP_CPP(${project}_stw_HEADERS_MOC ${${project}_stw_HEADERS})

add_library(${project}_stw STATIC ${${project}_stw_SRC} ${${project}_stw_HEADERS_MOC})

target_link_libraries(${project}_stw ${QT_LIBRARIES})

