# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/MinGW-Windows
TARGET = JAA
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
QT = core gui
SOURCES += Compressor/Codec/Codecs/RLE/codecRLE.cpp Compressor/Codec/codecAbstract.cpp Compressor/Codec/codec.cpp GUI/FileList/fileList.cpp GUI/SettingsPanels/decompressSetingsPanel.cpp main.cpp Compressor/DataBlock/dataBlockHeader.cpp Compressor/Codec/Codecs/HUFF/codecHUFF.cpp GUI/Face/face.cpp Compressor/DataBlock/dataBlock.cpp GUI/StatInfoW/statInfoW.cpp GUI/CompressorThread/compressorThread.cpp Compressor/Codec/Codecs/BWT/divsuf/divsufsort.cpp Compressor/Codec/Codecs/BWT/divsuf/sssort.cpp Compressor/FilesTable/fileBlocksInfo.cpp Compressor/Codec/Codecs/BWT/divsuf/trsort.cpp Compressor/FilesTable/filesTable.cpp Compressor/DataBlock/readerDataBlockHeader.cpp GUI/SettingsPanels/compressSettingsPanel.cpp Compressor/compressor.cpp Compressor/CRC/crc.cpp Compressor/Codec/Codecs/HUFF/shclib.cpp GUI/DataUnitsToQString/dataUnitsToQString.cpp Compressor/Codec/Codecs/BWT/codecBWT.cpp Compressor/Codec/Codecs/MTF/codecMTF.cpp
HEADERS += Compressor/CRC/crc.h Compressor/Codec/Codecs/HUFF/shclib.h Compressor/FilesTable/filesTable.h Compressor/compressor.h Compressor/Codec/codecAbstract.h Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h Compressor/Codec/codec.h Compressor/Codec/Codecs/BWT/codecBWT.h GUI/SettingsPanels/compressSettingsPanel.h GUI/StatInfoW/statInfoW.h Compressor/Codec/Codecs/HUFF/shc.h Compressor/DataBlock/readerDataBlockHeader.h Compressor/FilesTable/fileBlocksInfo.h Compressor/Codec/Codecs/RLE/codecRLE.h Compressor/Codec/Codecs/BWT/divsuf/divsufsort_private.h GUI/FileList/fileList.h GUI/CompressorThread/compressorThread.h Compressor/DataBlock/dataBlock.h Compressor/Codec/Codecs/MTF/codecMTF.h GUI/Face/face.h GUI/DataUnitsToQString/dataUnitsToQString.h Compressor/Codec/Codecs/HUFF/codecHUFF.h Compressor/private/consts.h Compressor/DataBlock/dataBlockHeader.h Compressor/Codec/Codecs/BWT/divsuf/lfs.h GUI/SettingsPanels/decompressSetingsPanel.h
FORMS += GUI/Face/face.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc.exe
QMAKE_CXX = g++.exe
DEFINES += 
INCLUDEPATH += 
LIBS += 
QMAKE_CXXFLAGS_DEBUG =  -Wextra -Winline -Wdisabled-optimization -Wunused-macros -Wunused-function -Wunused-parameter -Wunused-value -Wunused-variable -pedantic
