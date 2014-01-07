cmake_minimum_required(VERSION 2.8)

set(project "JAA")

cmake_policy(SET CMP0020 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ggdb -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x -ggdb -Wall -Wno-long-long -pedantic -Wextra -Wno-format-extra-args -Wformat=2 -Winit-self -Wmissing-include-dirs -Wsystem-headers -Wfloat-equal -Wconversion -Wlogical-op -Wmissing-noreturn -Wunreachable-code -Winline -Wdisabled-optimization -Woverlength-strings -Wold-style-cast -Woverloaded-virtual -Wsign-promo")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP")
endif()

find_package(Qt5Widgets REQUIRED)
add_definitions(${QT5_DEFINITIONS})


add_subdirectory(GUI)
add_subdirectory(Compressor)


include_directories(${CMAKE_SOURCE_DIR})



set(${project}_SRC main.cpp)

add_executable(${project} ${${project}_SRC})

qt5_use_modules(${project} Widgets Gui Core)

target_link_libraries(${project}
    ${QT_LIBRARIES}
    ${project}_face
    ${project}_compressor
    ${project}_codec
)


add_dependencies(${project} ${project}_face)
