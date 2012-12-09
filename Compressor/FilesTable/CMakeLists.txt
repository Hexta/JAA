cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(${project}_filestable_SRC
    fileBlocksInfo.cpp
    filesTable.cpp
)

include_directories(${CMAKE_SOURCE_DIR})


add_library(${project}_filestable STATIC
    ${${project}_filestable_SRC}
)

target_link_libraries(${project}_filestable
)

