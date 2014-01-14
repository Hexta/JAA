cmake_minimum_required(VERSION 2.8)

set(${PROJECT_NAME}_crc_SRC
       crc.cpp
)

include_directories(${CMAKE_SOURCE_DIR})


add_library(${PROJECT_NAME}_crc STATIC
    ${${PROJECT_NAME}_crc_SRC}
)

target_link_libraries(${PROJECT_NAME}_crc
)

