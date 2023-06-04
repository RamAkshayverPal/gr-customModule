/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_OFDM_FRAME_EQUAL_VCVC_IMPL_H
#define INCLUDED_CUSTOMMODULE_OFDM_FRAME_EQUAL_VCVC_IMPL_H

#include <gnuradio/customModule/ofdm_equalizer_base.h>
#include <gnuradio/customModule/ofdm_frame_equal_vcvc.h>


namespace gr {
namespace customModule {

class ofdm_frame_equal_vcvc_impl : public ofdm_frame_equal_vcvc
{
private:
    const int d_fft_len;
    const int d_cp_len;
    ofdm_equalizer_base::sptr d_eq;
    bool d_propagate_channel_state;
    const int d_fixed_frame_len;
    std::vector<gr_complex> d_channel_state;

protected:
    void parse_length_tags(const std::vector<std::vector<tag_t>>& tags,
                           gr_vector_int& n_input_items_reqd) override;

public:
    ofdm_frame_equal_vcvc_impl(gr::customModule::ofdm_equalizer_base::sptr equalizer,
                                   int cp_len,
                                   const std::string& len_tag_key,
                                   bool propagate_channel_state,
                                   int fixed_frame_len);
    ~ofdm_frame_equal_vcvc_impl() override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_int& ninput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_OFDM_FRAME_EQUAL_VCVC_IMPL_H */
