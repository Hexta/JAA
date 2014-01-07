cmake_minimum_required(VERSION 2.8)

find_package(Boost REQUIRED
)                  

set(${project}_filestable_SRC
    fileBlocksInfo.cpp
    filesTable.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
)


add_library(${project}_filestable STATIC
    ${${project}_filestable_SRC}
)

target_link_libraries(${project}_filestable
)
