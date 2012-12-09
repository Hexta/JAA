cmake_minimum_required(VERSION 2.8)

set(project "JAA")

FIND_PACKAGE(Qt4 REQUIRED)

set(${project}_SRC main.cpp)



add_subdirectory(GUI)
add_subdirectory(Compressor)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(${project} ${${project}_SRC})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})



target_link_libraries(${project}
    ${QT_LIBRARIES}
    ${project}_face
    ${project}_compressor
    ${project}_codec
)



add_dependencies(${project} ${project}_face)
