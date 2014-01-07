cmake_minimum_required(VERSION 2.8)

set(${project}_codec_rle_SRC
    codecRLE.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(${project}_codec_rle STATIC
    ${${project}_codec_rle_SRC}
)

target_link_libraries(${project}_codec_rle
)
