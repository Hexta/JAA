cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0020 NEW)

find_package(Qt5Widgets REQUIRED)
add_definitions(${QT5_DEFINITIONS})

set(${PROJECT_NAME}_face_SRC
    compressSettingsPanel.cpp
    compressorThread.cpp
    dataUnitsToQString.cpp
    decompressSetingsPanel.cpp
    face.cpp 
    fileList.cpp
    statInfoW.cpp
)

set(${PROJECT_NAME}_face_HEADERS_MOC
    compressSettingsPanel.h
    compressorThread.h
    decompressSetingsPanel.h
    face.h
    fileList.h
    statInfoW.h
)

set(${PROJECT_NAME}_face_HEADERS
    dataUnitsToQString.h
)

set(${PROJECT_NAME}_face_FORMS
    face.ui
)

QT5_WRAP_UI(${PROJECT_NAME}_face_FORMS_HEADERS ${${PROJECT_NAME}_face_FORMS})
QT5_WRAP_CPP(${PROJECT_NAME}_face_HEADERS_MOC ${${PROJECT_NAME}_face_HEADERS_MOC})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME}_Face STATIC
    ${${PROJECT_NAME}_face_SRC}
    ${${PROJECT_NAME}_face_FORMS_HEADERS}
    ${${PROJECT_NAME}_face_HEADERS_MOC}
    ${${PROJECT_NAME}_face_HEADERS}
)

qt5_use_modules(${PROJECT_NAME}_Face Widgets Gui Core)

target_link_libraries(${PROJECT_NAME}_Face
    ${QT_LIBRARIES}
    ${PROJECT_NAME}_compressor
)

