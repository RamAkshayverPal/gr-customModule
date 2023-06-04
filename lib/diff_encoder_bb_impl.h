/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_DIFF_ENCODER_BB_IMPL_H
#define INCLUDED_CUSTOMMODULE_DIFF_ENCODER_BB_IMPL_H

#include <gnuradio/customModule/diff_encoder_bb.h>

namespace gr {
namespace customModule {

class diff_encoder_bb_impl : public diff_encoder_bb
{
private:
    unsigned int d_last_out;
    const unsigned int d_modulus;
    const enum diff_coding_type d_coding;

public:
    diff_encoder_bb_impl(unsigned int modulus, enum diff_coding_type coding);
    ~diff_encoder_bb_impl() override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_DIFF_ENCODER_BB_IMPL_H */
