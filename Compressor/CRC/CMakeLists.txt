cmake_minimum_required(VERSION 2.8)

set(${PROJECT_NAME}_crc_SRC
    crc.cpp
)

set(${PROJECT_NAME}_crc_H
    crc.h
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME}_Crc STATIC
    ${${PROJECT_NAME}_crc_SRC}
    ${${PROJECT_NAME}_crc_H}
)
