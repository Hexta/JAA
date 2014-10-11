cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(${PROJECT_NAME}_datablock_SRC
    dataBlock.cpp
    dataBlockHeader.cpp
    readerDataBlockHeader.cpp
)

set(${PROJECT_NAME}_datablock_H
    dataBlock.h
    dataBlockHeader.h
    readerDataBlockHeader.h
)

include_directories(${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME}_Datablock STATIC
    ${${PROJECT_NAME}_datablock_SRC}
    ${${PROJECT_NAME}_datablock_H}
)

target_link_libraries(${PROJECT_NAME}_Datablock
    Qt5::Widgets
)
