cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(${project}_compressor_SRC
       compressor.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(Codec)
add_subdirectory(DataBlock)
add_subdirectory(FilesTable)
add_subdirectory(CRC)


add_library(${project}_compressor STATIC
    ${${project}_compressor_SRC}
)

target_link_libraries(${project}_compressor
    ${project}_codec
    ${project}_datablock
    ${project}_filestable
    ${project}_crc
)

