cmake_minimum_required(VERSION 2.8)

set(${PROJECT_NAME}_codec_rle_SRC
    codecRLE.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME}_codec_rle STATIC
    ${${PROJECT_NAME}_codec_rle_SRC}
)

target_link_libraries(${PROJECT_NAME}_codec_rle
)
