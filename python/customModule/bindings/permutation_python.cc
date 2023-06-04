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
/* BINDTOOL_HEADER_FILE(permutation.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(33f00e684f1f2f1988bae704b7e3919a)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/customModule/permutation.h>
// pydoc.h is automatically generated in the build directory
#include <permutation_pydoc.h>

void bind_permutation(py::module& m)
{

    using permutation = ::gr::customModule::permutation;


    py::class_<permutation,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<permutation>>(m, "permutation", D(permutation))

        .def(py::init(&permutation::make),
             py::arg("K"),
             py::arg("TABLE"),
             py::arg("SYMS_PER_BLOCK"),
             py::arg("NBYTES"),
             D(permutation, make))


        .def("K", &permutation::K, D(permutation, K))


        .def("TABLE", &permutation::TABLE, D(permutation, TABLE))


        .def("SYMS_PER_BLOCK",
             &permutation::SYMS_PER_BLOCK,
             D(permutation, SYMS_PER_BLOCK))


        .def("BYTES_PER_SYMBOL",
             &permutation::BYTES_PER_SYMBOL,
             D(permutation, BYTES_PER_SYMBOL))


        .def("set_K", &permutation::set_K, py::arg("K"), D(permutation, set_K))


        .def("set_TABLE",
             &permutation::set_TABLE,
             py::arg("table"),
             D(permutation, set_TABLE))


        .def("set_SYMS_PER_BLOCK",
             &permutation::set_SYMS_PER_BLOCK,
             py::arg("spb"),
             D(permutation, set_SYMS_PER_BLOCK))

        ;
}
