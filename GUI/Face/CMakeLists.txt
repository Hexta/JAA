cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(${project}_face_SRC
       face.cpp 
)

set(${project}_face_HEADERS
    face.h
)

set(${project}_face_FORMS
    face.ui
)


QT4_WRAP_UI(${project}_face_FORMS_HEADERS ${${project}_face_FORMS})
QT4_WRAP_CPP(${project}_face_HEADERS_MOC ${${project}_face_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})


add_library(${project}_face STATIC
    ${${project}_face_SRC}
    ${${project}_face_FORMS_HEADERS}
    ${${project}_face_HEADERS_MOC}
)

target_link_libraries(${project}_face
    ${QT_LIBRARIES}
    ${project}_ct
    ${project}_filelist    
    ${project}_settings_panel
    ${project}_stw
    ${project}_dus
)

