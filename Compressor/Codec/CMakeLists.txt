cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_NAME}_codec_SRC
    codecAbstract.cpp
    codec.cpp
)

set(${PROJECT_NAME}_codec_H
    codecAbstract.h
    codec.h
)

set(${PROJECT_NAME}_codec_bwt_SRC
    BWT/codecBWT.cpp
)

set(${PROJECT_NAME}_codec_bwt_H
    BWT/codecBWT.h
)

set(${PROJECT_NAME}_divsuf_SRC
    BWT/divsuf/divsufsort.cpp
    BWT/divsuf/sssort.cpp
    BWT/divsuf/trsort.cpp
)

set(${PROJECT_NAME}_divsuf_H
    BWT/divsuf/divsufsort.h
    BWT/divsuf/divsufsort_private.h
    BWT/divsuf/lfs.h
)

set(${PROJECT_NAME}_codec_huff_SRC
    HUFF/codecHUFF.cpp
    HUFF/shclib.cpp
)

set(${PROJECT_NAME}_codec_huff_H
    HUFF/codecHUFF.h
    HUFF/shc.h
    HUFF/shclib.h
)

set(${PROJECT_NAME}_codec_mtf_SRC
    MTF/codecMTF.cpp
)

set(${PROJECT_NAME}_codec_mtf_H
    MTF/codecMTF.h
)

set(${PROJECT_NAME}_codec_rle_SRC
    RLE/codecRLE.cpp
)

set(${PROJECT_NAME}_codec_rle_H
    RLE/codecRLE.h
)

source_group(BWT FILES
    ${${PROJECT_NAME}_codec_bwt_SRC}
    ${${PROJECT_NAME}_codec_bwt_H}
)

source_group(BWT\\divsuf FILES
    ${${PROJECT_NAME}_divsuf_SRC}
    ${${PROJECT_NAME}_divsuf_H}
)

source_group(HUFF FILES
    ${${PROJECT_NAME}_codec_huff_SRC}
    ${${PROJECT_NAME}_codec_huff_H}
)

source_group(MTF FILES
    ${${PROJECT_NAME}_codec_mtf_SRC}
    ${${PROJECT_NAME}_codec_mtf_H}
)

source_group(RLE FILES
    ${${PROJECT_NAME}_codec_rle_SRC}
    ${${PROJECT_NAME}_codec_rle_H}
)

add_library(${PROJECT_NAME}_Codec STATIC
    ${${PROJECT_NAME}_codec_SRC}
    ${${PROJECT_NAME}_codec_H}
    ${${PROJECT_NAME}_codec_bwt_SRC}
    ${${PROJECT_NAME}_codec_bwt_H}
    ${${PROJECT_NAME}_codec_huff_SRC}
    ${${PROJECT_NAME}_codec_huff_H}
    ${${PROJECT_NAME}_codec_mtf_SRC}
    ${${PROJECT_NAME}_codec_mtf_H}
    ${${PROJECT_NAME}_codec_rle_SRC}
    ${${PROJECT_NAME}_codec_rle_H}
    ${${PROJECT_NAME}_divsuf_SRC}
    ${${PROJECT_NAME}_divsuf_H}
)
