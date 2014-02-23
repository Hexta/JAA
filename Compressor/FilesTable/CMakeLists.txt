cmake_minimum_required(VERSION 2.8)

find_package(Boost REQUIRED
)                  

set(${PROJECT_NAME}_filestable_SRC
    fileBlocksInfo.cpp
    filesTable.cpp
)

set(${PROJECT_NAME}_filestable_H
    fileBlocksInfo.h
    filesTable.h
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}_Filestable STATIC
    ${${PROJECT_NAME}_filestable_SRC}
    ${${PROJECT_NAME}_filestable_H}
)
