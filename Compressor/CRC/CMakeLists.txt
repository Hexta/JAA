cmake_minimum_required(VERSION 2.8)

set(${project}_crc_SRC
       crc.cpp
)

include_directories(${CMAKE_SOURCE_DIR})


add_library(${project}_crc STATIC
    ${${project}_crc_SRC}
)

target_link_libraries(${project}_crc
)

