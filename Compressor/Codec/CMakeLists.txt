cmake_minimum_required(VERSION 2.8)

set(${PROJECT_NAME}_codec_SRC
       codecAbstract.cpp
       codec.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(Codecs)


add_library(${PROJECT_NAME}_codec STATIC
    ${${PROJECT_NAME}_codec_SRC}
)

target_link_libraries(${PROJECT_NAME}_codec
    ${PROJECT_NAME}_codec_bwt
    ${PROJECT_NAME}_codec_huff
    ${PROJECT_NAME}_codec_mtf
    ${PROJECT_NAME}_codec_rle
)
