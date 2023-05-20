/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Equalizer_mux_impl.h"
#include <gnuradio/io_signature.h>
#include <algorithm>
#include <numeric>
namespace gr {
namespace customModule {

Equalizer_mux::sptr Equalizer_mux::make(int Vectorsize)
{
    return gnuradio::make_block_sptr<Equalizer_mux_impl>(Vectorsize);
}


/*
 * The private constructor
 */
Equalizer_mux_impl::Equalizer_mux_impl(int Vectorsize)
    : gr::sync_block("Equalizer_mux",
                     gr::io_signature::make2(
                         2 /* min inputs */, 2 /* max inputs */, sizeof(gr_complex)*Vectorsize, sizeof(gr_complex)*Vectorsize),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(gr_complex)*Vectorsize))
{
    index = {6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58};
    ctaps = std::vector<float>(64, 0);
    ind = std::vector<int>{8, 16, 20, 28, 36, 44, 48, 56};
    for (const auto& i : index)
        ctaps[i] = 1;
    for (const auto& i : ind)
        ctaps[i] = 2;
    taps.assign(ctaps.begin(), ctaps.end());
    this->message_port_register_in(pmt::mp("TapsIn"));
    this->set_msg_handler(pmt::mp("TapsIn"), [this](pmt::pmt_t msg) { this->handler(msg); });
}

/*
 * Our virtual destructor.
 */
Equalizer_mux_impl::~Equalizer_mux_impl() {}

void Equalizer_mux_impl::handler(const pmt::pmt_t& msg_pmt)
{
        size_t length;
        const float* elements = pmt::f32vector_elements(msg_pmt, length);
        ctaps.assign(elements, elements + length);
 }

int Equalizer_mux_impl::work(int noutput_items,
                             gr_vector_const_void_star& input_items,
                             gr_vector_void_star& output_items)
{
    auto in0 = static_cast< const gr_complex*>(input_items[0]);
    auto in1 = static_cast< const gr_complex*>(input_items[1]);
    auto out = static_cast<gr_complex*>(output_items[0]);
    
    for ( int vect = 0; vect < noutput_items; vect++) {
        std::vector<float> req_taps(index.size());
        for (unsigned int i = 0; i < index.size(); i++){
            req_taps[i] = ctaps[index[i]];
            }
        int decimals = 0;
        for(unsigned int i=0; i< index.size(); i++){
           req_taps[i] = std::round(req_taps[i] * std::pow(10, decimals)) / std::pow(10, decimals);
        }
        std::vector<size_t> sorted_index(req_taps.size());
        std::iota(sorted_index.begin(), sorted_index.end(), 0); // Initialize index vector with consecutive integers
        std::stable_sort(sorted_index.begin(), sorted_index.end(), [&req_taps](size_t i, size_t j){
        return req_taps[i] > req_taps[j]; // Sort the index vector in descending order of corresponding elements in req_taps
        });
        std::vector<int>hig_8_sorted_index(8, 0);
        for(int i=0; i<8; i++){
           hig_8_sorted_index[i] = sorted_index[i];
        }
        for(unsigned int i=0; i< hig_8_sorted_index.size(); i++){
            if(hig_8_sorted_index[i]>=0 && hig_8_sorted_index[i]<5){
                hig_8_sorted_index[i] += 6;
            }
            else if(hig_8_sorted_index[i]>=6 && hig_8_sorted_index[i]<19){
                hig_8_sorted_index[i] += 7;
            }
            else if(hig_8_sorted_index[i]>=20 && hig_8_sorted_index[i]<26){
                hig_8_sorted_index[i] += 8;
            }
            else if(hig_8_sorted_index[i]>=27 && hig_8_sorted_index[i]<33){
                hig_8_sorted_index[i] += 9;
            }
            else if(hig_8_sorted_index[i]>=34 && hig_8_sorted_index[i]<43){
                hig_8_sorted_index[i] += 10;
            }
            else{
                hig_8_sorted_index[i] += 11;
            }
        }
        //for(unsigned int i=0; i<hig_8_sorted_index.size(); i++){
            //in0[hig_8_sorted_index[i]] = in1[hig_8_sorted_index[i]];
       // }
        for(int i=0; i<64; i++){
            auto it = std::find(hig_8_sorted_index.begin(), hig_8_sorted_index.end(), i);
            if(it != hig_8_sorted_index.end()){
                out[vect*64 + i] = in1[vect*64 + i];
            }
            else{
                out[vect*64 + i] = in0[vect*64 + i];
            }
            
        }
            
      }
    
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
