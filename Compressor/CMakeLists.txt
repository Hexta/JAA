cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0020 NEW)
find_package(Qt5Widgets REQUIRED)
add_definitions(${QT5_DEFINITIONS})

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

qt5_use_modules(${project}_compressor Widgets Gui Core)

target_link_libraries(${project}_compressor
    ${project}_codec
    ${project}_datablock
    ${project}_filestable
    ${project}_crc
)
