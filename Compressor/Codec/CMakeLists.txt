cmake_minimum_required(VERSION 2.8)

set(${project}_codec_SRC
       codecAbstract.cpp
       codec.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(Codecs)


add_library(${project}_codec STATIC
    ${${project}_codec_SRC}
)

target_link_libraries(${project}_codec
    ${project}_codec_bwt
    ${project}_codec_huff
    ${project}_codec_mtf
    ${project}_codec_rle
)
