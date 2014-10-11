cmake_minimum_required(VERSION 2.8.11)

set(${PROJECT_NAME}_compressor_SRC
       compressor.cpp
)

set(${PROJECT_NAME}_compressor_H
       compressor.h
)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(Codec)
add_subdirectory(DataBlock)
add_subdirectory(FilesTable)
add_subdirectory(CRC)

add_library(${PROJECT_NAME}_compressor STATIC
    ${${PROJECT_NAME}_compressor_SRC}
    ${${PROJECT_NAME}_compressor_H}
)

target_link_libraries(${PROJECT_NAME}_compressor
    ${PROJECT_NAME}_Codec
    ${PROJECT_NAME}_Datablock
    ${PROJECT_NAME}_Filestable
    ${PROJECT_NAME}_Crc
)
