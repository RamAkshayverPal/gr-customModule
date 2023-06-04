/*
 * Copyright 2023 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(ofdm_equalizer_simpledfe.h) */
/* BINDTOOL_HEADER_FILE_HASH(f58d8b2c99cb26d021ce7c4cf225ecd1)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/customModule/ofdm_equalizer_simpledfe.h>
// pydoc.h is automatically generated in the build directory
#include <ofdm_equalizer_simpledfe_pydoc.h>

void bind_ofdm_equalizer_simpledfe(py::module& m)
{

    using ofdm_equalizer_simpledfe = ::gr::customModule::ofdm_equalizer_simpledfe;


    py::class_<ofdm_equalizer_simpledfe,
               gr::customModule::ofdm_equalizer_1d_pilots,
               std::shared_ptr<ofdm_equalizer_simpledfe>>(
        m, "ofdm_equalizer_simpledfe", D(ofdm_equalizer_simpledfe))

        .def(py::init(&ofdm_equalizer_simpledfe::make),
             py::arg("fft_len"),
             py::arg("constellation"),
             py::arg("occupied_carriers") = std::vector<std::vector<int>>(),
             py::arg("pilot_carriers") = std::vector<std::vector<int>>(),
             py::arg("pilot_symbols") = std::vector<std::vector<gr_complex>>(),
             py::arg("symbols_skipped") = 0,
             py::arg("alpha") = 0.10000000000000001,
             py::arg("input_is_shifted") = true,
             py::arg("enable_soft_output") = false,
             D(ofdm_equalizer_simpledfe, make))


        .def("equalize",
             &ofdm_equalizer_simpledfe::equalize,
             py::arg("frame"),
             py::arg("n_sym"),
             py::arg("initial_taps") = std::vector<gr_complex>(),
             py::arg("tags") = std::vector<gr::tag_t>(),
             D(ofdm_equalizer_simpledfe, equalize))


        ;
}
