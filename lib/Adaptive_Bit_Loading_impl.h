/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_ADAPTIVE_BIT_LOADING_IMPL_H
#define INCLUDED_CUSTOMMODULE_ADAPTIVE_BIT_LOADING_IMPL_H

#include <gnuradio/customModule/Adaptive_Bit_Loading.h>
#include <gnuradio/msg_queue.h>
#include <gnuradio/block.h>
#include <gnuradio/thread/thread.h>
namespace gr {
namespace customModule {

class Adaptive_Bit_Loading_impl : public Adaptive_Bit_Loading
{
private:
    bool selector;
    std::vector<float> ctaps;
    std::vector<float> taps;
    std::vector<int> index;
    std::vector<int> ind;

public:
    Adaptive_Bit_Loading_impl(int Occupied_Carriers);
    ~Adaptive_Bit_Loading_impl() override;
    void handler(const pmt::pmt_t& msg_pmt);
    //bool select(bool msg_select, const pmt::pmt_t& msg_pmt);
    //void set_ctaps(const std::vector<float>& ctap);
    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_ADAPTIVE_BIT_LOADING_IMPL_H */
