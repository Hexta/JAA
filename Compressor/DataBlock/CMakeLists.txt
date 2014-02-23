cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0020 NEW)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

add_definitions(${QT5_DEFINITIONS})

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

qt5_use_modules(${PROJECT_NAME}_Datablock Widgets Gui Core OpenGL)

target_link_libraries(${PROJECT_NAME}_Datablock
    ${QT_LIBRARIES}
)
