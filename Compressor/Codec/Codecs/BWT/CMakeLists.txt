cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(${project}_codec_bwt_SRC
    codecBWT.cpp
)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(divsuf)


add_library(${project}_codec_bwt STATIC
    ${${project}_codec_bwt_SRC}
)

target_link_libraries(${project}_codec_bwt
    ${project}_divsuf
)

