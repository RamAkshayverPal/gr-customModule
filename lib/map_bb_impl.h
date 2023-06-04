/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_MAP_BB_IMPL_H
#define INCLUDED_CUSTOMMODULE_MAP_BB_IMPL_H

#include <gnuradio/customModule/map_bb.h>

namespace gr {
namespace customModule {

class map_bb_impl : public map_bb
{
private:
    static constexpr size_t s_map_size = 0x100;
    unsigned char d_map[s_map_size];
    mutable gr::thread::mutex d_mutex;

public:
    map_bb_impl(const std::vector<int>& map);
    ~map_bb_impl();
    
    void set_map(const std::vector<int>& map) override;
    std::vector<int> map() const override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_MAP_BB_IMPL_H */
