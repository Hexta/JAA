cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE(Qt4 REQUIRED)

set(${project}_dus_SRC
    dataUnitsToQString.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_library(${project}_dus STATIC ${${project}_dus_SRC})

target_link_libraries(${project}_dus ${QT_LIBRARIES})

