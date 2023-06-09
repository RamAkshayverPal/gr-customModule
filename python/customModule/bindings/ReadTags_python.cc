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
/* BINDTOOL_HEADER_FILE(ReadTags.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(eea12f8fa558c31f6547726d3d0dd8ab)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/customModule/ReadTags.h>
// pydoc.h is automatically generated in the build directory
#include <ReadTags_pydoc.h>

void bind_ReadTags(py::module& m)
{

    using ReadTags    = gr::customModule::ReadTags;


    py::class_<ReadTags, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<ReadTags>>(m, "ReadTags", D(ReadTags))

        .def(py::init(&ReadTags::make),
           D(ReadTags,make)
        )
        



        ;




}








