cmake_minimum_required(VERSION 2.8)

set(${project}_codec_mtf_SRC
    codecMTF.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(${project}_codec_mtf STATIC
    ${${project}_codec_mtf_SRC}
)

target_link_libraries(${project}_codec_mtf
)
