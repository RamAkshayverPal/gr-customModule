/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ReadTags_impl.h"
#include <gnuradio/io_signature.h>
#include <string>
using namespace std;
namespace gr {
namespace customModule {


ReadTags::sptr ReadTags::make(std::string tag_key)
{
    return gnuradio::make_block_sptr<ReadTags_impl>(tag_key);
}


/*
 * The private constructor
 */
ReadTags_impl::ReadTags_impl(std::string tag_key)
    : gr::sync_block("ReadTags",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(gr_complex)),
                     gr::io_signature::make(
                         0/* min outputs */, 0 /*max outputs */, 0/*sizeof(gr_complex)*/))
{
    index = {6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58};
    ctaps = std::vector<gr_complex>(64, gr_complex(0.0f,0.0f));
    ind = std::vector<int>{8, 16, 20, 28, 36, 44, 48, 56};
    for (const auto& i : index)
        ctaps[i] = gr_complex(1.0f, 0.0f);
    for (const auto& i : ind)
        ctaps[i] = gr_complex(2.0f, 0.0f);
    pmt::pmt_t ctaps_out = pmt::mp("ctaps_out");
    this->message_port_register_out(pmt::mp("ctaps_out"));
}

/*
 * Our virtual destructor.
 */
ReadTags_impl::~ReadTags_impl() {}

int ReadTags_impl::work(int noutput_items,
                        gr_vector_const_void_star& input_items,
                        gr_vector_void_star& output_items)
{
    auto in = static_cast<const gr_complex*>(input_items[0]);
    //auto out = static_cast<gr_complex*>(output_items[0]);
    std::vector<tag_t> tags;
    get_tags_in_window(tags, 0, 0, input_items.size());
    for (unsigned i = 0; i < tags.size(); i++) {
        if (pmt::symbol_to_string(tags[i].key) == "ofdm_sync_chan_taps") {
            ctaps = pmt::c32vector_elements(tags[i].value);
        }
       }
    
    std::vector<float> ctap(64, 0.0f);
    for(unsigned int i=0; i<ctaps.size(); i++){
        ctap[i] = std::abs(ctaps[i]);
    }
    
    pmt::pmt_t pmt_msg = pmt::init_f32vector(ctap.size(), ctap.data());
    message_port_pub(pmt::mp("ctaps_out"), pmt_msg);
    //for(unsigned int i=0; i< input_items.size(); i++){
        //out[i] = in[i];
    //}
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
