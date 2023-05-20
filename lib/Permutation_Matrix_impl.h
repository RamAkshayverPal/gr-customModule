/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_PERMUTATION_MATRIX_IMPL_H
#define INCLUDED_CUSTOMMODULE_PERMUTATION_MATRIX_IMPL_H

#include <gnuradio/customModule/Permutation_Matrix.h>

namespace gr {
namespace customModule {

class Permutation_Matrix_impl : public Permutation_Matrix
{
private:
    bool selector;
    std::vector<float> ctaps;
    std::vector<float> taps;
    std::vector<int> index;
    std::vector<int> ind;
    int Occupied_Carriers;
public:
    Permutation_Matrix_impl(int Occupied_Carriers);
    ~Permutation_Matrix_impl() override;
     
     void handler(const pmt::pmt_t& msg_pmt);
    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_PERMUTATION_MATRIX_IMPL_H */
