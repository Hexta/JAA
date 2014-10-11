cmake_minimum_required(VERSION 2.8.11)

project("JAA")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ggdb -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x -ggdb -Wall -Wno-long-long -pedantic -Wextra -Wno-format-extra-args -Wformat=2 -Winit-self -Wmissing-include-dirs -Wsystem-headers -Wfloat-equal -Wconversion -Wlogical-op -Wmissing-noreturn -Wunreachable-code -Winline -Wdisabled-optimization -Woverlength-strings -Wold-style-cast -Woverloaded-virtual -Wsign-promo")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ggdb -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x -g -fno-omit-frame-pointer -Wall -Wextra -pedantic -Weverything -Wnosystem-headers")
endif()

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

add_subdirectory(GUI)
add_subdirectory(Compressor)

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_NAME}_SRC main.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
    ${PROJECT_NAME}_Face
    ${PROJECT_NAME}_compressor
    ${PROJECT_NAME}_Codec
)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_Face)
