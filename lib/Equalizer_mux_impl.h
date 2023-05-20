/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_EQUALIZER_MUX_IMPL_H
#define INCLUDED_CUSTOMMODULE_EQUALIZER_MUX_IMPL_H

#include <gnuradio/customModule/Equalizer_mux.h>

namespace gr {
namespace customModule {

class Equalizer_mux_impl : public Equalizer_mux
{
private:
    std::vector<float> ctaps;
    std::vector<float> taps;
    std::vector<int> index;
    std::vector<int> ind;

public:
    Equalizer_mux_impl(int Vectorsize);
    ~Equalizer_mux_impl() override;
    void handler(const pmt::pmt_t& msg_pmt);
    
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_EQUALIZER_MUX_IMPL_H */
