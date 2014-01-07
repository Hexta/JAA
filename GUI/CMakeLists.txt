cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0020 NEW)

find_package(Qt5Widgets REQUIRED)
add_definitions(${QT5_DEFINITIONS})

set(${project}_face_SRC
    compressSettingsPanel.cpp
    compressorThread.cpp
    dataUnitsToQString.cpp
    decompressSetingsPanel.cpp
    face.cpp 
    fileList.cpp
    statInfoW.cpp
)

set(${project}_face_HEADERS
    compressSettingsPanel.h
    compressorThread.h
    decompressSetingsPanel.h
    face.h
    fileList.h
    statInfoW.h
)

set(${project}_face_FORMS
    face.ui
)


QT5_WRAP_UI(${project}_face_FORMS_HEADERS ${${project}_face_FORMS})
QT5_WRAP_CPP(${project}_face_HEADERS_MOC ${${project}_face_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})


add_library(${project}_face STATIC
    ${${project}_face_SRC}
    ${${project}_face_FORMS_HEADERS}
    ${${project}_face_HEADERS_MOC}
)

qt5_use_modules(${project}_face Widgets Gui Core)

target_link_libraries(${project}_face
    ${QT_LIBRARIES}
    ${project}_compressor
)

