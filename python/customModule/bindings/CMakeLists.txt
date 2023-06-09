# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT customModule_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT customModule_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################
list(APPEND customModule_python_files
    ReadTags_python.cc
    Adaptive_Bit_Loading_python.cc
    Permutation_Matrix_python.cc
    Equalizer_mux_python.cc
    metric_type_python.cc
    constellation_python.cc
    ofdm_equalizer_base_python.cc
    ofdm_equalizer_simpledfe_python.cc
    ofdm_frame_equal_vcvc_python.cc
    map_bb_python.cc
    diff_coding_type_python.cc
    diff_encoder_bb_python.cc
    chunks_to_symbols_python.cc
    control_loop_python.cc
    control_loop_python.cc
    permutation_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(customModule
   ../../..
   gr::customModule
   "${customModule_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET customModule_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:customModule_python>
    ${PROJECT_BINARY_DIR}/test_modules/gnuradio/customModule/
)

install(TARGETS customModule_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/customModule COMPONENT pythonapi)
