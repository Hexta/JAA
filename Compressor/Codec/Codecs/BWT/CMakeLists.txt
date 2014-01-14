cmake_minimum_required(VERSION 2.8)

set(${PROJECT_NAME}_codec_bwt_SRC
    codecBWT.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(divsuf)


add_library(${PROJECT_NAME}_codec_bwt STATIC
    ${${PROJECT_NAME}_codec_bwt_SRC}
)

target_link_libraries(${PROJECT_NAME}_codec_bwt
    ${PROJECT_NAME}_divsuf
)
