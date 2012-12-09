cmake_minimum_required(VERSION 2.8)

set(${project}_divsuf_SRC
    divsufsort.cpp
    sssort.cpp
    trsort.cpp
)

include_directories(${CMAKE_SOURCE_DIR})


add_library(${project}_divsuf STATIC
    ${${project}_divsuf_SRC}
)

target_link_libraries(${project}_divsuf
)

