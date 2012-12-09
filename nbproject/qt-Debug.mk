#############################################################################
# Makefile for building: JAA
# Generated by qmake (2.01a) (Qt 4.7.0) on: ?? 12. ??? 23:17:27 2011
# Project:  nbproject/qt-Debug.pro
# Template: app
# Command: c:/Qt/2010.05/qt/bin/qmake.exe VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc.exe
CXX           = g++.exe
DEFINES       = -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_GUI_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -DQT_NEEDS_QMAIN
CFLAGS        = -g -Wall $(DEFINES)
CXXFLAGS      = -Wextra -Winline -Wdisabled-optimization -Wunused-macros -Wunused-function -Wunused-parameter -Wunused-value -Wunused-variable -pedantic -frtti -fexceptions -mthreads -Wall $(DEFINES)
INCPATH       = -I'../../Qt/2010.05/qt/include/QtCore' -I'../../Qt/2010.05/qt/include/QtGui' -I'../../Qt/2010.05/qt/include' -I'../../Qt/2010.05/qt/include/ActiveQt' -I'.' -I'.' -I'nbproject' -I'.' -I'../../Qt/2010.05/qt/mkspecs/default'
LINK        =        g++
LFLAGS        =        -enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -mthreads -Wl -Wl,-subsystem,windows
LIBS        =        -L'c:/Qt/2010.05/qt/lib' -lmingw32 -lqtmaind build/Debug/MinGW-Windows/JAA_resource_res.o -lQtGuid4 -lQtCored4 
QMAKE         = c:/Qt/2010.05/qt/bin/qmake.exe
IDC           = c:/Qt/2010.05/qt/binidc.exe
IDL           = midl
ZIP           = zip -r -9
DEF_FILE      = 
RES_FILE      = build/Debug/MinGW-Windows/JAA_resource_res.o
COPY          = cp
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
DEL_FILE      = rm
DEL_DIR       = rmdir
MOVE          = mv
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir
INSTALL_FILE    = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR     = $(COPY_DIR)

####### Output directory

OBJECTS_DIR   = build/Debug/MinGW-Windows/

####### Files

SOURCES       = Compressor/Codec/Codecs/RLE/codecRLE.cpp \
		Compressor/Codec/codecAbstract.cpp \
		Compressor/Codec/codec.cpp \
		GUI/FileList/fileList.cpp \
		GUI/SettingsPanels/decompressSetingsPanel.cpp \
		main.cpp \
		Compressor/DataBlock/dataBlockHeader.cpp \
		Compressor/Codec/Codecs/HUFF/codecHUFF.cpp \
		GUI/Face/face.cpp \
		Compressor/DataBlock/dataBlock.cpp \
		GUI/StatInfoW/statInfoW.cpp \
		GUI/CompressorThread/compressorThread.cpp \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.cpp \
		Compressor/Codec/Codecs/BWT/divsuf/sssort.cpp \
		Compressor/FilesTable/fileBlocksInfo.cpp \
		Compressor/Codec/Codecs/BWT/divsuf/trsort.cpp \
		Compressor/FilesTable/filesTable.cpp \
		Compressor/DataBlock/readerDataBlockHeader.cpp \
		GUI/SettingsPanels/compressSettingsPanel.cpp \
		Compressor/compressor.cpp \
		Compressor/CRC/crc.cpp \
		Compressor/Codec/Codecs/HUFF/shclib.cpp \
		GUI/DataUnitsToQString/dataUnitsToQString.cpp \
		Compressor/Codec/Codecs/BWT/codecBWT.cpp \
		Compressor/Codec/Codecs/MTF/codecMTF.cpp moc_compressSettingsPanel.cpp \
		moc_statInfoW.cpp \
		moc_fileList.cpp \
		moc_compressorThread.cpp \
		moc_face.cpp \
		moc_decompressSetingsPanel.cpp
OBJECTS       = build/Debug/MinGW-Windows/codecRLE.o \
		build/Debug/MinGW-Windows/codecAbstract.o \
		build/Debug/MinGW-Windows/codec.o \
		build/Debug/MinGW-Windows/fileList.o \
		build/Debug/MinGW-Windows/decompressSetingsPanel.o \
		build/Debug/MinGW-Windows/main.o \
		build/Debug/MinGW-Windows/dataBlockHeader.o \
		build/Debug/MinGW-Windows/codecHUFF.o \
		build/Debug/MinGW-Windows/face.o \
		build/Debug/MinGW-Windows/dataBlock.o \
		build/Debug/MinGW-Windows/statInfoW.o \
		build/Debug/MinGW-Windows/compressorThread.o \
		build/Debug/MinGW-Windows/divsufsort.o \
		build/Debug/MinGW-Windows/sssort.o \
		build/Debug/MinGW-Windows/fileBlocksInfo.o \
		build/Debug/MinGW-Windows/trsort.o \
		build/Debug/MinGW-Windows/filesTable.o \
		build/Debug/MinGW-Windows/readerDataBlockHeader.o \
		build/Debug/MinGW-Windows/compressSettingsPanel.o \
		build/Debug/MinGW-Windows/compressor.o \
		build/Debug/MinGW-Windows/crc.o \
		build/Debug/MinGW-Windows/shclib.o \
		build/Debug/MinGW-Windows/dataUnitsToQString.o \
		build/Debug/MinGW-Windows/codecBWT.o \
		build/Debug/MinGW-Windows/codecMTF.o \
		build/Debug/MinGW-Windows/moc_compressSettingsPanel.o \
		build/Debug/MinGW-Windows/moc_statInfoW.o \
		build/Debug/MinGW-Windows/moc_fileList.o \
		build/Debug/MinGW-Windows/moc_compressorThread.o \
		build/Debug/MinGW-Windows/moc_face.o \
		build/Debug/MinGW-Windows/moc_decompressSetingsPanel.o
DIST          = 
QMAKE_TARGET  = JAA
DESTDIR        = dist/Debug/MinGW-Windows/ #avoid trailing-slash linebreak
TARGET         = JAA.exe
DESTDIR_TARGET = dist/Debug/MinGW-Windows/JAA.exe

####### Implicit rules

.SUFFIXES: .cpp .cc .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

first: all
all: qttmp-Debug.mk  $(DESTDIR_TARGET)

$(DESTDIR_TARGET): ui_face.h $(OBJECTS) build/Debug/MinGW-Windows/JAA_resource_res.o
	$(LINK) $(LFLAGS) -o $(DESTDIR_TARGET) object_script.JAA  $(LIBS)


build/Debug/MinGW-Windows/JAA_resource_res.o: JAA_resource.rc
	windres -i JAA_resource.rc -o build/Debug/MinGW-Windows/JAA_resource_res.o --include-dir=. $(DEFINES)

qttmp-Debug.mk: nbproject/qt-Debug.pro  ../../Qt/2010.05/qt/mkspecs/qconfig.pri \
		../../Qt/2010.05/qt/mkspecs/modules/qt_webkit_version.pri \
		../../Qt/2010.05/qt/mkspecs/features/qt_functions.prf \
		../../Qt/2010.05/qt/mkspecs/features/qt_config.prf \
		../../Qt/2010.05/qt/mkspecs/features/exclusive_builds.prf \
		../../Qt/2010.05/qt/mkspecs/features/default_pre.prf \
		../../Qt/2010.05/qt/mkspecs/features/win32/default_pre.prf \
		../../Qt/2010.05/qt/mkspecs/features/debug.prf \
		../../Qt/2010.05/qt/mkspecs/features/default_post.prf \
		../../Qt/2010.05/qt/mkspecs/features/win32/default_post.prf \
		../../Qt/2010.05/qt/mkspecs/features/win32/rtti.prf \
		../../Qt/2010.05/qt/mkspecs/features/win32/exceptions.prf \
		../../Qt/2010.05/qt/mkspecs/features/win32/stl.prf \
		../../Qt/2010.05/qt/mkspecs/features/shared.prf \
		../../Qt/2010.05/qt/mkspecs/features/warn_on.prf \
		../../Qt/2010.05/qt/mkspecs/features/qt.prf \
		../../Qt/2010.05/qt/mkspecs/features/win32/thread.prf \
		../../Qt/2010.05/qt/mkspecs/features/moc.prf \
		../../Qt/2010.05/qt/mkspecs/features/win32/windows.prf \
		../../Qt/2010.05/qt/mkspecs/features/resources.prf \
		../../Qt/2010.05/qt/mkspecs/features/uic.prf \
		../../Qt/2010.05/qt/mkspecs/features/yacc.prf \
		../../Qt/2010.05/qt/mkspecs/features/lex.prf \
		../../Qt/2010.05/qt/mkspecs/features/include_source_dir.prf \
		c:/Qt/2010.05/qt/lib/qtmaind.prl
	$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
../../Qt/2010.05/qt/mkspecs/qconfig.pri:
../../Qt/2010.05/qt/mkspecs/modules/qt_webkit_version.pri:
../../Qt/2010.05/qt/mkspecs/features/qt_functions.prf:
../../Qt/2010.05/qt/mkspecs/features/qt_config.prf:
../../Qt/2010.05/qt/mkspecs/features/exclusive_builds.prf:
../../Qt/2010.05/qt/mkspecs/features/default_pre.prf:
../../Qt/2010.05/qt/mkspecs/features/win32/default_pre.prf:
../../Qt/2010.05/qt/mkspecs/features/debug.prf:
../../Qt/2010.05/qt/mkspecs/features/default_post.prf:
../../Qt/2010.05/qt/mkspecs/features/win32/default_post.prf:
../../Qt/2010.05/qt/mkspecs/features/win32/rtti.prf:
../../Qt/2010.05/qt/mkspecs/features/win32/exceptions.prf:
../../Qt/2010.05/qt/mkspecs/features/win32/stl.prf:
../../Qt/2010.05/qt/mkspecs/features/shared.prf:
../../Qt/2010.05/qt/mkspecs/features/warn_on.prf:
../../Qt/2010.05/qt/mkspecs/features/qt.prf:
../../Qt/2010.05/qt/mkspecs/features/win32/thread.prf:
../../Qt/2010.05/qt/mkspecs/features/moc.prf:
../../Qt/2010.05/qt/mkspecs/features/win32/windows.prf:
../../Qt/2010.05/qt/mkspecs/features/resources.prf:
../../Qt/2010.05/qt/mkspecs/features/uic.prf:
../../Qt/2010.05/qt/mkspecs/features/yacc.prf:
../../Qt/2010.05/qt/mkspecs/features/lex.prf:
../../Qt/2010.05/qt/mkspecs/features/include_source_dir.prf:
c:/Qt/2010.05/qt/lib/qtmaind.prl:
qmake:  FORCE
	@$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

dist:
	$(ZIP) JAA.zip $(SOURCES) $(DIST) nbproject/nbproject/qt-Debug.pro ../../Qt/2010.05/qt/mkspecs/qconfig.pri ../../Qt/2010.05/qt/mkspecs/modules/qt_webkit_version.pri ../../Qt/2010.05/qt/mkspecs/features/qt_functions.prf ../../Qt/2010.05/qt/mkspecs/features/qt_config.prf ../../Qt/2010.05/qt/mkspecs/features/exclusive_builds.prf ../../Qt/2010.05/qt/mkspecs/features/default_pre.prf ../../Qt/2010.05/qt/mkspecs/features/win32/default_pre.prf ../../Qt/2010.05/qt/mkspecs/features/debug.prf ../../Qt/2010.05/qt/mkspecs/features/default_post.prf ../../Qt/2010.05/qt/mkspecs/features/win32/default_post.prf ../../Qt/2010.05/qt/mkspecs/features/win32/rtti.prf ../../Qt/2010.05/qt/mkspecs/features/win32/exceptions.prf ../../Qt/2010.05/qt/mkspecs/features/win32/stl.prf ../../Qt/2010.05/qt/mkspecs/features/shared.prf ../../Qt/2010.05/qt/mkspecs/features/warn_on.prf ../../Qt/2010.05/qt/mkspecs/features/qt.prf ../../Qt/2010.05/qt/mkspecs/features/win32/thread.prf ../../Qt/2010.05/qt/mkspecs/features/moc.prf ../../Qt/2010.05/qt/mkspecs/features/win32/windows.prf ../../Qt/2010.05/qt/mkspecs/features/resources.prf ../../Qt/2010.05/qt/mkspecs/features/uic.prf ../../Qt/2010.05/qt/mkspecs/features/yacc.prf ../../Qt/2010.05/qt/mkspecs/features/lex.prf ../../Qt/2010.05/qt/mkspecs/features/include_source_dir.prf c:/Qt/2010.05/qt/lib/qtmaind.prl  HEADERS RESOURCES IMAGES SOURCES OBJECTIVE_SOURCES FORMS YACCSOURCES YACCSOURCES LEXSOURCES 

clean: compiler_clean 
	-$(DEL_FILE) build/Debug/MinGW-Windows/codecRLE.o build/Debug/MinGW-Windows/codecAbstract.o build/Debug/MinGW-Windows/codec.o build/Debug/MinGW-Windows/fileList.o build/Debug/MinGW-Windows/decompressSetingsPanel.o build/Debug/MinGW-Windows/main.o build/Debug/MinGW-Windows/dataBlockHeader.o build/Debug/MinGW-Windows/codecHUFF.o build/Debug/MinGW-Windows/face.o build/Debug/MinGW-Windows/dataBlock.o build/Debug/MinGW-Windows/statInfoW.o build/Debug/MinGW-Windows/compressorThread.o build/Debug/MinGW-Windows/divsufsort.o build/Debug/MinGW-Windows/sssort.o build/Debug/MinGW-Windows/fileBlocksInfo.o build/Debug/MinGW-Windows/trsort.o build/Debug/MinGW-Windows/filesTable.o build/Debug/MinGW-Windows/readerDataBlockHeader.o build/Debug/MinGW-Windows/compressSettingsPanel.o build/Debug/MinGW-Windows/compressor.o build/Debug/MinGW-Windows/crc.o build/Debug/MinGW-Windows/shclib.o build/Debug/MinGW-Windows/dataUnitsToQString.o build/Debug/MinGW-Windows/codecBWT.o build/Debug/MinGW-Windows/codecMTF.o build/Debug/MinGW-Windows/moc_compressSettingsPanel.o build/Debug/MinGW-Windows/moc_statInfoW.o build/Debug/MinGW-Windows/moc_fileList.o build/Debug/MinGW-Windows/moc_compressorThread.o build/Debug/MinGW-Windows/moc_face.o build/Debug/MinGW-Windows/moc_decompressSetingsPanel.o
	-$(DEL_FILE) build/Debug/MinGW-Windows/JAA_resource_res.o

distclean: clean
	-$(DEL_FILE) $(DESTDIR_TARGET)
	-$(DEL_FILE) qttmp-Debug.mk

check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_compressSettingsPanel.cpp moc_statInfoW.cpp moc_fileList.cpp moc_compressorThread.cpp moc_face.cpp moc_decompressSetingsPanel.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_compressSettingsPanel.cpp moc_statInfoW.cpp moc_fileList.cpp moc_compressorThread.cpp moc_face.cpp moc_decompressSetingsPanel.cpp
moc_compressSettingsPanel.cpp: GUI/SettingsPanels/compressSettingsPanel.h
	C:/Qt/2010.05/qt/binmoc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 GUI/SettingsPanels/compressSettingsPanel.h -o moc_compressSettingsPanel.cpp

moc_statInfoW.cpp: GUI/StatInfoW/statInfoW.h
	C:/Qt/2010.05/qt/binmoc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 GUI/StatInfoW/statInfoW.h -o moc_statInfoW.cpp

moc_fileList.cpp: GUI/CompressorThread/compressorThread.h \
		GUI/FileList/fileList.h
	C:/Qt/2010.05/qt/binmoc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 GUI/FileList/fileList.h -o moc_fileList.cpp

moc_compressorThread.cpp: GUI/CompressorThread/compressorThread.h
	C:/Qt/2010.05/qt/binmoc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 GUI/CompressorThread/compressorThread.h -o moc_compressorThread.cpp

moc_face.cpp: ui_face.h \
		Compressor/compressor.h \
		Compressor/Codec/codec.h \
		Compressor/Codec/Codecs/BWT/codecBWT.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h \
		Compressor/Codec/Codecs/MTF/codecMTF.h \
		Compressor/Codec/Codecs/RLE/codecRLE.h \
		Compressor/Codec/Codecs/HUFF/codecHUFF.h \
		Compressor/FilesTable/filesTable.h \
		Compressor/FilesTable/fileBlocksInfo.h \
		Compressor/DataBlock/dataBlockHeader.h \
		GUI/CompressorThread/compressorThread.h \
		GUI/Face/face.h
	C:/Qt/2010.05/qt/binmoc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 GUI/Face/face.h -o moc_face.cpp

moc_decompressSetingsPanel.cpp: GUI/SettingsPanels/decompressSetingsPanel.h
	C:/Qt/2010.05/qt/binmoc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 GUI/SettingsPanels/decompressSetingsPanel.h -o moc_decompressSetingsPanel.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_face.h
compiler_uic_clean:
	-$(DEL_FILE) ui_face.h
ui_face.h: GUI/Face/face.ui
	c:/Qt/2010.05/qt/binuic.exe GUI/Face/face.ui -o ui_face.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 



####### Compile

build/Debug/MinGW-Windows/codecRLE.o: Compressor/Codec/Codecs/RLE/codecRLE.cpp Compressor/Codec/Codecs/RLE/codecRLE.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/codecRLE.o Compressor/Codec/Codecs/RLE/codecRLE.cpp

build/Debug/MinGW-Windows/codecAbstract.o: Compressor/Codec/codecAbstract.cpp Compressor/Codec/codecAbstract.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/DataBlock/dataBlockHeader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/codecAbstract.o Compressor/Codec/codecAbstract.cpp

build/Debug/MinGW-Windows/codec.o: Compressor/Codec/codec.cpp Compressor/Codec/codec.h \
		Compressor/Codec/Codecs/BWT/codecBWT.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h \
		Compressor/Codec/Codecs/MTF/codecMTF.h \
		Compressor/Codec/Codecs/RLE/codecRLE.h \
		Compressor/Codec/Codecs/HUFF/codecHUFF.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/codec.o Compressor/Codec/codec.cpp

build/Debug/MinGW-Windows/fileList.o: GUI/FileList/fileList.cpp GUI/FileList/fileList.h \
		GUI/CompressorThread/compressorThread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/fileList.o GUI/FileList/fileList.cpp

build/Debug/MinGW-Windows/decompressSetingsPanel.o: GUI/SettingsPanels/decompressSetingsPanel.cpp GUI/SettingsPanels/decompressSetingsPanel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/decompressSetingsPanel.o GUI/SettingsPanels/decompressSetingsPanel.cpp

build/Debug/MinGW-Windows/main.o: main.cpp GUI/Face/face.h \
		ui_face.h \
		Compressor/compressor.h \
		Compressor/Codec/codec.h \
		Compressor/Codec/Codecs/BWT/codecBWT.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h \
		Compressor/Codec/Codecs/MTF/codecMTF.h \
		Compressor/Codec/Codecs/RLE/codecRLE.h \
		Compressor/Codec/Codecs/HUFF/codecHUFF.h \
		Compressor/FilesTable/filesTable.h \
		Compressor/FilesTable/fileBlocksInfo.h \
		Compressor/DataBlock/dataBlockHeader.h \
		GUI/CompressorThread/compressorThread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/main.o main.cpp

build/Debug/MinGW-Windows/dataBlockHeader.o: Compressor/DataBlock/dataBlockHeader.cpp Compressor/DataBlock/dataBlockHeader.h \
		Compressor/CRC/crc.h \
		Compressor/private/consts.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/dataBlockHeader.o Compressor/DataBlock/dataBlockHeader.cpp

build/Debug/MinGW-Windows/codecHUFF.o: Compressor/Codec/Codecs/HUFF/codecHUFF.cpp Compressor/Codec/Codecs/HUFF/codecHUFF.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h \
		Compressor/Codec/Codecs/HUFF/shclib.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/codecHUFF.o Compressor/Codec/Codecs/HUFF/codecHUFF.cpp

build/Debug/MinGW-Windows/face.o: GUI/Face/face.cpp GUI/Face/face.h \
		ui_face.h \
		Compressor/compressor.h \
		Compressor/Codec/codec.h \
		Compressor/Codec/Codecs/BWT/codecBWT.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h \
		Compressor/Codec/Codecs/MTF/codecMTF.h \
		Compressor/Codec/Codecs/RLE/codecRLE.h \
		Compressor/Codec/Codecs/HUFF/codecHUFF.h \
		Compressor/FilesTable/filesTable.h \
		Compressor/FilesTable/fileBlocksInfo.h \
		Compressor/DataBlock/dataBlockHeader.h \
		GUI/CompressorThread/compressorThread.h \
		GUI/FileList/fileList.h \
		GUI/SettingsPanels/compressSettingsPanel.h \
		GUI/SettingsPanels/decompressSetingsPanel.h \
		GUI/StatInfoW/statInfoW.h \
		GUI/DataUnitsToQString/dataUnitsToQString.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/face.o GUI/Face/face.cpp

build/Debug/MinGW-Windows/dataBlock.o: Compressor/DataBlock/dataBlock.cpp Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/DataBlock/dataBlockHeader.h \
		Compressor/DataBlock/readerDataBlockHeader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/dataBlock.o Compressor/DataBlock/dataBlock.cpp

build/Debug/MinGW-Windows/statInfoW.o: GUI/StatInfoW/statInfoW.cpp GUI/StatInfoW/statInfoW.h \
		GUI/DataUnitsToQString/dataUnitsToQString.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/statInfoW.o GUI/StatInfoW/statInfoW.cpp

build/Debug/MinGW-Windows/compressorThread.o: GUI/CompressorThread/compressorThread.cpp GUI/CompressorThread/compressorThread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/compressorThread.o GUI/CompressorThread/compressorThread.cpp

build/Debug/MinGW-Windows/divsufsort.o: Compressor/Codec/Codecs/BWT/divsuf/divsufsort.cpp Compressor/Codec/Codecs/BWT/divsuf/divsufsort_private.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/divsufsort.o Compressor/Codec/Codecs/BWT/divsuf/divsufsort.cpp

build/Debug/MinGW-Windows/sssort.o: Compressor/Codec/Codecs/BWT/divsuf/sssort.cpp Compressor/Codec/Codecs/BWT/divsuf/divsufsort_private.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/sssort.o Compressor/Codec/Codecs/BWT/divsuf/sssort.cpp

build/Debug/MinGW-Windows/fileBlocksInfo.o: Compressor/FilesTable/fileBlocksInfo.cpp Compressor/FilesTable/fileBlocksInfo.h \
		Compressor/private/consts.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/fileBlocksInfo.o Compressor/FilesTable/fileBlocksInfo.cpp

build/Debug/MinGW-Windows/trsort.o: Compressor/Codec/Codecs/BWT/divsuf/trsort.cpp Compressor/Codec/Codecs/BWT/divsuf/divsufsort_private.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/trsort.o Compressor/Codec/Codecs/BWT/divsuf/trsort.cpp

build/Debug/MinGW-Windows/filesTable.o: Compressor/FilesTable/filesTable.cpp Compressor/FilesTable/filesTable.h \
		Compressor/FilesTable/fileBlocksInfo.h \
		Compressor/DataBlock/dataBlockHeader.h \
		Compressor/CRC/crc.h \
		Compressor/private/consts.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/filesTable.o Compressor/FilesTable/filesTable.cpp

build/Debug/MinGW-Windows/readerDataBlockHeader.o: Compressor/DataBlock/readerDataBlockHeader.cpp Compressor/DataBlock/readerDataBlockHeader.h \
		Compressor/DataBlock/dataBlockHeader.h \
		Compressor/CRC/crc.h \
		Compressor/private/consts.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/readerDataBlockHeader.o Compressor/DataBlock/readerDataBlockHeader.cpp

build/Debug/MinGW-Windows/compressSettingsPanel.o: GUI/SettingsPanels/compressSettingsPanel.cpp GUI/SettingsPanels/compressSettingsPanel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/compressSettingsPanel.o GUI/SettingsPanels/compressSettingsPanel.cpp

build/Debug/MinGW-Windows/compressor.o: Compressor/compressor.cpp Compressor/compressor.h \
		Compressor/Codec/codec.h \
		Compressor/Codec/Codecs/BWT/codecBWT.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h \
		Compressor/Codec/Codecs/MTF/codecMTF.h \
		Compressor/Codec/Codecs/RLE/codecRLE.h \
		Compressor/Codec/Codecs/HUFF/codecHUFF.h \
		Compressor/FilesTable/filesTable.h \
		Compressor/FilesTable/fileBlocksInfo.h \
		Compressor/DataBlock/dataBlockHeader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/compressor.o Compressor/compressor.cpp

build/Debug/MinGW-Windows/crc.o: Compressor/CRC/crc.cpp Compressor/CRC/crc.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/crc.o Compressor/CRC/crc.cpp

build/Debug/MinGW-Windows/shclib.o: Compressor/Codec/Codecs/HUFF/shclib.cpp Compressor/Codec/Codecs/HUFF/shc.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/shclib.o Compressor/Codec/Codecs/HUFF/shclib.cpp

build/Debug/MinGW-Windows/dataUnitsToQString.o: GUI/DataUnitsToQString/dataUnitsToQString.cpp GUI/DataUnitsToQString/dataUnitsToQString.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/dataUnitsToQString.o GUI/DataUnitsToQString/dataUnitsToQString.cpp

build/Debug/MinGW-Windows/codecBWT.o: Compressor/Codec/Codecs/BWT/codecBWT.cpp Compressor/Codec/Codecs/BWT/codecBWT.h \
		Compressor/Codec/Codecs/BWT/divsuf/divsufsort.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/codecBWT.o Compressor/Codec/Codecs/BWT/codecBWT.cpp

build/Debug/MinGW-Windows/codecMTF.o: Compressor/Codec/Codecs/MTF/codecMTF.cpp Compressor/Codec/Codecs/MTF/codecMTF.h \
		Compressor/DataBlock/dataBlock.h \
		Compressor/private/consts.h \
		Compressor/CRC/crc.h \
		Compressor/Codec/codecAbstract.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/codecMTF.o Compressor/Codec/Codecs/MTF/codecMTF.cpp

build/Debug/MinGW-Windows/moc_compressSettingsPanel.o: moc_compressSettingsPanel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/moc_compressSettingsPanel.o moc_compressSettingsPanel.cpp

build/Debug/MinGW-Windows/moc_statInfoW.o: moc_statInfoW.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/moc_statInfoW.o moc_statInfoW.cpp

build/Debug/MinGW-Windows/moc_fileList.o: moc_fileList.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/moc_fileList.o moc_fileList.cpp

build/Debug/MinGW-Windows/moc_compressorThread.o: moc_compressorThread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/moc_compressorThread.o moc_compressorThread.cpp

build/Debug/MinGW-Windows/moc_face.o: moc_face.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/moc_face.o moc_face.cpp

build/Debug/MinGW-Windows/moc_decompressSetingsPanel.o: moc_decompressSetingsPanel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW-Windows/moc_decompressSetingsPanel.o moc_decompressSetingsPanel.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

