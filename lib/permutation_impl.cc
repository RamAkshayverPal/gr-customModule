/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "permutation_impl.h"
#include <gnuradio/io_signature.h>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric> 
#include <pmt/pmt.h>
#include <iterator>
namespace gr {
namespace customModule {

permutation::sptr permutation::make(int K,
                                    const std::vector<int>& TABLE,
                                    int SYMS_PER_BLOCK,
                                    size_t BYTES_PER_SYMBOL)
{
    return gnuradio::make_block_sptr<permutation_impl>(
        K, TABLE, SYMS_PER_BLOCK, BYTES_PER_SYMBOL);
}

permutation_impl::permutation_impl(int K,
                                   const std::vector<int>& TABLE,
                                   int SYMS_PER_BLOCK,
                                   size_t BYTES_PER_SYMBOL)
    : sync_block("permutation",
                 io_signature::make(1, -1, BYTES_PER_SYMBOL),
                 io_signature::make(1, -1, BYTES_PER_SYMBOL)),
      d_K(K),
      d_TABLE(TABLE),
      d_SYMS_PER_BLOCK(SYMS_PER_BLOCK),
      d_BYTES_PER_SYMBOL(BYTES_PER_SYMBOL)
{
    set_output_multiple(d_K * d_SYMS_PER_BLOCK);
    // std::cout << d_K << "\n";
    index = {6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58};
    ctaps = std::vector<float>(64, 0);
    ind = std::vector<int>{8, 16, 20, 28, 36, 44, 48, 56};
    for (const auto& i : index)
        ctaps[i] = 1;
    for (const auto& i : ind)
        ctaps[i] = 2;
    this->message_port_register_in(pmt::mp("TapsIn"));
    this->set_msg_handler(pmt::mp("TapsIn"), [this](pmt::pmt_t msg) { this->handler(msg); });
}

void permutation_impl::set_K(int K)
{
    gr::thread::scoped_lock guard(d_setlock);
    d_K = K;
    set_output_multiple(d_K * d_SYMS_PER_BLOCK);
}
void permutation_impl::handler(const pmt::pmt_t& msg_pmt)
{
        size_t length;
        const float* elements = pmt::f32vector_elements(msg_pmt, length);
        ctaps.assign(elements, elements + length);
        std::vector<float> req_taps(index.size());
        for (unsigned int i = 0; i < index.size(); i++){
            req_taps[i] = ctaps[index[i]];
        }
        for(unsigned int i=0; i< index.size(); i++){
            req_taps[i] = std::round(req_taps[i]);
            }
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
        set_TABLE(perm);
 }
void permutation_impl::set_TABLE(const std::vector<int>& table)
{
    gr::thread::scoped_lock guard(d_setlock);
    d_TABLE = table;
}

void permutation_impl::set_SYMS_PER_BLOCK(int spb)
{
    gr::thread::scoped_lock guard(d_setlock);
    d_SYMS_PER_BLOCK = spb;
    set_output_multiple(d_K * d_SYMS_PER_BLOCK);
}

permutation_impl::~permutation_impl() {}

int permutation_impl::work(int noutput_items,
                           gr_vector_const_void_star& input_items,
                           gr_vector_void_star& output_items)
{
    gr::thread::scoped_lock guard(d_setlock);
    int nstreams = input_items.size();

    for (int m = 0; m < nstreams; m++) {
        const char* in = (const char*)input_items[m];
        char* out = (char*)output_items[m];

        // per stream processing
        for (int i = 0; i < noutput_items / d_SYMS_PER_BLOCK; i++) {
            // Index i refers to blocks.
            // Beginning of packet (in blocks)
            int i0 = d_K * (i / d_K);
            // position of block within packet (in blocks)
            int j0 = i % d_K;
            // new position of block within packet (in blocks)
            int k0 = d_TABLE[j0];
            memcpy(&(out[i * d_SYMS_PER_BLOCK * d_BYTES_PER_SYMBOL]),
                   &(in[(i0 + k0) * d_SYMS_PER_BLOCK * d_BYTES_PER_SYMBOL]),
                   d_BYTES_PER_SYMBOL * d_SYMS_PER_BLOCK);
        }
        // end per stream processing
    }
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
