cmake_minimum_required(VERSION 2.8)

set(project "JAA")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})


add_subdirectory(GUI)
add_subdirectory(Compressor)


include_directories(${CMAKE_SOURCE_DIR})



set(${project}_SRC main.cpp)

add_executable(${project} ${${project}_SRC})

target_link_libraries(${project}
    ${QT_LIBRARIES}
    ${project}_face
    ${project}_compressor
    ${project}_codec
)


add_dependencies(${project} ${project}_face)
