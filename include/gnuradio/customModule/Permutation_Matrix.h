/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_PERMUTATION_MATRIX_H
#define INCLUDED_CUSTOMMODULE_PERMUTATION_MATRIX_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API Permutation_Matrix : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<Permutation_Matrix> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of customModule::Permutation_Matrix.
     *
     * To avoid accidental use of raw pointers, customModule::Permutation_Matrix's
     * constructor is in a private implementation
     * class. customModule::Permutation_Matrix::make is the public interface for
     * creating new instances.
     */
    static sptr make(int Occupied_Carriers = 48);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_PERMUTATION_MATRIX_H */
