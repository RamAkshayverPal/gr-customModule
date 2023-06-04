/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <pybind11/pybind11.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

namespace py = pybind11;

// Headers for binding functions
/**************************************/
// The following comment block is used for
// gr_modtool to insert function prototypes
// Please do not delete
/**************************************/
// BINDING_FUNCTION_PROTOTYPES(
    void bind_ReadTags(py::module& m);
    void bind_Adaptive_Bit_Loading(py::module& m);
    void bind_Permutation_Matrix(py::module& m);
    void bind_Equalizer_mux(py::module& m);
    void bind_metric_type(py::module& m);
    void bind_constellation(py::module& m);
    void bind_ofdm_equalizer_base(py::module& m);
    void bind_ofdm_equalizer_simpledfe(py::module& m);
    void bind_ofdm_frame_equal_vcvc(py::module& m);
    void bind_map_bb(py::module& m);
    void bind_diff_coding_type(py::module& m);
    void bind_diff_encoder_bb(py::module& m);
    void bind_chunks_to_symbols(py::module& m);
    void bind_control_loop(py::module& m);
    void bind_permutation(py::module& m);
// ) END BINDING_FUNCTION_PROTOTYPES


// We need this hack because import_array() returns NULL
// for newer Python versions.
// This function is also necessary because it ensures access to the C API
// and removes a warning.
void* init_numpy()
{
    import_array();
    return NULL;
}

PYBIND11_MODULE(customModule_python, m)
{
    // Initialize the numpy C API
    // (otherwise we will see segmentation faults)
    init_numpy();

    // Allow access to base block methods
    py::module::import("gnuradio.gr");

    /**************************************/
    // The following comment block is used for
    // gr_modtool to insert binding function calls
    // Please do not delete
    /**************************************/
    // BINDING_FUNCTION_CALLS(
    bind_ReadTags(m);
    bind_Adaptive_Bit_Loading(m);
    bind_Permutation_Matrix(m);
    bind_Equalizer_mux(m);
    bind_metric_type(m);
    bind_constellation(m);
    bind_ofdm_equalizer_base(m);
    bind_ofdm_equalizer_simpledfe(m);
    bind_ofdm_frame_equal_vcvc(m);
    bind_map_bb(m);
    bind_diff_coding_type(m);
    bind_diff_encoder_bb(m);
    bind_chunks_to_symbols(m);
    bind_control_loop(m);
    bind_permutation(m);
    // ) END BINDING_FUNCTION_CALLS
}