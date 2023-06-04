/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Adaptive_Bit_Loading_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/block.h>
#include <cmath>
#include <algorithm>
#include <numeric> 
#include <pmt/pmt.h>
#include <iterator>
#include <gnuradio/thread/thread.h>
namespace gr {
namespace customModule {

Adaptive_Bit_Loading::sptr Adaptive_Bit_Loading::make(int Occupied_Carriers)
{
    return gnuradio::make_block_sptr<Adaptive_Bit_Loading_impl>(Occupied_Carriers);
}


/*
 * The private constructor
 */
Adaptive_Bit_Loading_impl::Adaptive_Bit_Loading_impl(int Occupied_Carriers)
    : gr::sync_block("Adaptive Bit Loading",
                    gr::io_signature::make2(2, 2, sizeof(gr_complex) * 40, sizeof(gr_complex) * 8),
                    gr::io_signature::make2(2, 2, sizeof(gr_complex) * Occupied_Carriers, sizeof(float) * Occupied_Carriers))
{
    selector = true;
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
Adaptive_Bit_Loading_impl::~Adaptive_Bit_Loading_impl() {}

void Adaptive_Bit_Loading_impl::handler(const pmt::pmt_t& msg_pmt)
{
        size_t length;
        const float* elements = pmt::f32vector_elements(msg_pmt, length);
        ctaps.assign(elements, elements + length);
 }
int Adaptive_Bit_Loading_impl::work(int noutput_items,
                                    gr_vector_const_void_star& input_items,
                                    gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const gr_complex*>(input_items[0]);
    auto in1 = static_cast<const gr_complex*>(input_items[1]);
    auto out0 = static_cast<gr_complex*>(output_items[0]);
    auto out1 = static_cast<float*>(output_items[1]);
    //selector = true;
    for ( int vect = 0; vect < noutput_items; vect++) {
        
       // if(selector){ 
            std::vector<float> req_taps(index.size());
            for (unsigned int i = 0; i < index.size(); i++){
                req_taps[i] = ctaps[index[i]];
                
            }
            //int decimals = 0;
            for(unsigned int i=0; i< index.size(); i++)
                req_taps[i] = std::round(req_taps[i]);// * std::pow(10, decimals)) / std::pow(10, decimals);
            //for(unsigned int i=0; i< index.size(); i++)    
                //out1[vect*index.size() + i] = req_taps[i];
            std::vector<size_t> sorted_index(req_taps.size());
            std::iota(sorted_index.begin(), sorted_index.end(), 0); // Initialize index vector with consecutive integers
            std::stable_sort(sorted_index.begin(), sorted_index.end(), [&req_taps](size_t i, size_t j){
            return req_taps[i] > req_taps[j]; // Sort the index vector in descending order of corresponding elements in req_taps
            });
            std::vector<int> m(index.size(), 0);
            for(unsigned int i=0;i<index.size(); i++){
                if(i<8){
                    m[sorted_index[i]] = 1;
                }
            }
            for(unsigned int i=0;i<index.size(); i++){
                out1[vect*index.size() + i] = m[i];
            }
            std::vector<std::complex<float>> outp(index.size(), std::complex<float>(1.0f, 0.0f));
            int j =0;
            int k =0;
            for (unsigned int i = 0;i<index.size(); i++) {
                if (m[i] == 1) {
                    outp[i] = in1[vect*8 + j];
                    j = j+1;
                } 
                else {
                    outp[i] = in0[vect*40 + k];
                    k= k+1;
                }
            }
            for(unsigned int i =0;i<index.size(); i++){
                out0[vect*index.size() + i] = outp[i];
            }
         //}
             
             
       /* else{
            std::vector<float> req_taps(index.size());
            for (unsigned int i = 0; i < index.size(); i++){
                req_taps[i] = taps[index[i]];
                out1[vect*index.size() + i] = req_taps[i];
            }
            int decimals = 0;
            for(unsigned int i=0; i< index.size(); i++)
                req_taps[i] = std::round(req_taps[i] * std::pow(10, decimals)) / std::pow(10, decimals);
            std::vector<size_t> sorted_index(req_taps.size());
            std::iota(sorted_index.begin(), sorted_index.end(), 0); // Initialize index vector with consecutive integers
            std::stable_sort(sorted_index.begin(), sorted_index.end(), [&req_taps](size_t i, size_t j){
            return req_taps[i] > req_taps[j]; // Sort the index vector in descending order of corresponding elements in req_taps
            });
            std::vector<int> m(index.size(), 0);
            for(unsigned int i=0;i<index.size(); i++){
                if(i<8){
                    m[sorted_index[i]] = 1;
                }
            }
            std::vector<std::complex<float>> outp(index.size(), std::complex<float>(1.0f, 0.0f));
            int j =0;
            int k =0;
            for (unsigned int i = 0;i<index.size(); i++) {
                if (m[i] == 1) {
                    outp[i] = in1[vect*8+j];
                    j = j+1;
                } 
                else {
                    outp[i] = in0[vect*40 + k];
                    k= k+1;
                }
            }
            for(unsigned int i =0;i<index.size(); i++){
                out0[vect*index.size() + i] = outp[i];
            }
     }*/
    }
    
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */

