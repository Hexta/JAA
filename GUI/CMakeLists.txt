cmake_minimum_required(VERSION 2.8.11)

set(${PROJECT_NAME}_face_SRC
    compressSettingsPanel.cpp
    compressorThread.cpp
    dataUnitsToQString.cpp
    decompressSetingsPanel.cpp
    face.cpp 
    fileList.cpp
    statInfoW.cpp
)

set(${PROJECT_NAME}_face_HEADERS
    dataUnitsToQString.h
    compressSettingsPanel.h
    compressorThread.h
    decompressSetingsPanel.h
    face.h
    fileList.h
    statInfoW.h
)

set(${PROJECT_NAME}_face_FORMS
    face.ui
)

QT5_WRAP_UI(${PROJECT_NAME}_face_FORMS_HEADERS ${${PROJECT_NAME}_face_FORMS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME}_Face STATIC
    ${${PROJECT_NAME}_face_SRC}
    ${${PROJECT_NAME}_face_FORMS_HEADERS}
    ${${PROJECT_NAME}_face_HEADERS}
)

target_link_libraries(${PROJECT_NAME}_Face
    Qt5::Widgets
    ${PROJECT_NAME}_compressor
)
