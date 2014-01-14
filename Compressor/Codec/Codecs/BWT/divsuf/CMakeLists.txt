cmake_minimum_required(VERSION 2.8)

set(${PROJECT_NAME}_divsuf_SRC
    divsufsort.cpp
    sssort.cpp
    trsort.cpp
)

include_directories(${CMAKE_SOURCE_DIR})


add_library(${PROJECT_NAME}_divsuf STATIC
    ${${PROJECT_NAME}_divsuf_SRC}
)

target_link_libraries(${PROJECT_NAME}_divsuf
)

