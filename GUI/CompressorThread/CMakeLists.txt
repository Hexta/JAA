cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(${project}_ct_SRC
    compressorThread.cpp
)

set(${project}_ct_HEADERS
    compressorThread.h
)

include_directories(${CMAKE_SOURCE_DIR})


QT4_WRAP_CPP(${project}_ct_HEADERS_MOC ${${project}_ct_HEADERS})
add_library(${project}_ct STATIC ${${project}_ct_SRC} ${${project}_ct_HEADERS_MOC})

target_link_libraries(${project}_ct
    ${QT_LIBRARIES}
    ${project}_compressor
)

