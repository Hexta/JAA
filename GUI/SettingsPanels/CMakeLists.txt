cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(${project}_settings_panel_SRC
    compressSettingsPanel.cpp
    decompressSetingsPanel.cpp
)

set(${project}_settings_panel_HEADERS
    compressSettingsPanel.h
    decompressSetingsPanel.h
)

include_directories(${CMAKE_SOURCE_DIR})

QT4_WRAP_CPP(${project}_settings_panel_HEADERS_MOC ${${project}_settings_panel_HEADERS})

add_library(${project}_settings_panel STATIC ${${project}_settings_panel_SRC} ${${project}_settings_panel_HEADERS_MOC})

target_link_libraries(${project}_settings_panel ${QT_LIBRARIES})

