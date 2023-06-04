/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Permutation_Matrix_impl.h"
#include <gnuradio/io_signature.h>
#include <algorithm>
#include <numeric>

namespace gr {
namespace customModule {


Permutation_Matrix::sptr Permutation_Matrix::make(int Occupied_Carriers)
{
    return gnuradio::make_block_sptr<Permutation_Matrix_impl>(Occupied_Carriers);
}


/*
 * The private constructor
 */
Permutation_Matrix_impl::Permutation_Matrix_impl(int Occupied_Carriers)
    : gr::sync_block("Permutation_Matrix",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(gr_complex)*Occupied_Carriers),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(gr_complex)*Occupied_Carriers))
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
Permutation_Matrix_impl::~Permutation_Matrix_impl() {}

void Permutation_Matrix_impl::handler(const pmt::pmt_t& msg_pmt)
{
        size_t length;
        const float* elements = pmt::f32vector_elements(msg_pmt, length);
        ctaps.assign(elements, elements + length);
 }

int Permutation_Matrix_impl::work(int noutput_items,
                                  gr_vector_const_void_star& input_items,
                                  gr_vector_void_star& output_items)
{
    auto in = static_cast<const gr_complex*>(input_items[0]);
    auto out = static_cast<gr_complex*>(output_items[0]);
    std::vector<int>n;
    for(unsigned int i=0; i<index.size(); i++){
        n.push_back(i);
    }
    std::vector<std::vector<float>>A(index.size(), std::vector<float>(index.size(),0.0f));
    for ( int vect = 0; vect < noutput_items; vect++) {
            std::vector<float> req_taps(index.size());
            for (unsigned int i = 0; i < index.size(); i++){
                req_taps[i] = ctaps[index[i]];
            }
            int decimals = 0;
            for(unsigned int i=0; i< index.size(); i++)
                req_taps[i] = std::round(req_taps[i] * std::pow(10, decimals)) / std::pow(10, decimals);
            std::vector<size_t> sorted_index(req_taps.size());
            std::iota(sorted_index.begin(), sorted_index.end(), 0); // Initialize index vector with consecutive integers
            std::stable_sort(sorted_index.begin(), sorted_index.end(), [&req_taps](size_t i, size_t j){
            return req_taps[i] > req_taps[j]; // Sort the index vector in descending order of corresponding elements in req_taps
            });
            
            std::vector<int>perm(index.size());
            for(unsigned int i=0; i<index.size(); i++){
                perm[i] = sorted_index[i];
            }
            
            std::rotate(perm.begin(), perm.begin() + 8, perm.end());
    
            for(auto i: n){
                  A[i][perm[i]] = 1.0;
            }
           for (unsigned int i = 0; i < A.size(); i++)
           {
	       for (unsigned int j = 0; j < A[0].size(); j++)
	       {
	       if(A[i][j]){
	          out[vect*index.size()+ i] = A[i][j] * in[vect*index.size()+j];
	          }
	      }
           }
        }    
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
