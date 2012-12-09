cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(${project}_filelist_SRC
    fileList.cpp
)

set(${project}_filelist_HEADERS
    fileList.h
)

include_directories(${CMAKE_SOURCE_DIR})


QT4_WRAP_CPP(${project}_filelist_HEADERS_MOC ${${project}_filelist_HEADERS})

add_library(${project}_filelist STATIC ${${project}_filelist_SRC} ${${project}_filelist_HEADERS_MOC})

target_link_libraries(${project}_filelist
    ${QT_LIBRARIES}
)

