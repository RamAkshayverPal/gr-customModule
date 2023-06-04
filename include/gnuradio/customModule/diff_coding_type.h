/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_DIFF_CODING_TYPE_H
#define INCLUDED_CUSTOMMODULE_DIFF_CODING_TYPE_H

#include <gnuradio/customModule/api.h>

namespace gr {
namespace customModule {

// Differential coding types
enum diff_coding_type {
    DIFF_DIFFERENTIAL = 0, // Standard differential coding x[n] - x[n-1] % M
    DIFF_NRZI = 1,         // NRZI coding
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_DIFF_CODING_TYPE_H */
