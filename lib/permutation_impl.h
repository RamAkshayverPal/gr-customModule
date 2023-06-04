/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_PERMUTATION_IMPL_H
#define INCLUDED_CUSTOMMODULE_PERMUTATION_IMPL_H

#include <gnuradio/customModule/permutation.h>
#include <pmt/pmt.h>
namespace gr {
namespace customModule {

class permutation_impl : public permutation
{
private:
    int d_K;
    std::vector<int> d_TABLE;
    int d_SYMS_PER_BLOCK;
    size_t d_BYTES_PER_SYMBOL;
    std::vector<float> ctaps;
    std::vector<int> index;
    std::vector<int> ind;
public:
    permutation_impl(int K,
                     const std::vector<int>& TABLE,
                     int SYMS_PER_BLOCK,
                     size_t NBYTES);
    ~permutation_impl() override;

    int K() const override { return d_K; }
    std::vector<int> TABLE() const override { return d_TABLE; }
    int SYMS_PER_BLOCK() const override { return d_SYMS_PER_BLOCK; }
    size_t BYTES_PER_SYMBOL() const override { return d_BYTES_PER_SYMBOL; }

    void set_K(int K) override;
    void set_TABLE(const std::vector<int>& table) override;
    void set_SYMS_PER_BLOCK(int spb) override;
    void handler(const pmt::pmt_t& msg_pmt);
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} /* namespace customModule */
} /* namespace gr */

#endif /* INCLUDED_CUSTOMMODULE_PERMUTATION_IMPL_H */
