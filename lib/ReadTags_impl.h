/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_READTAGS_IMPL_H
#define INCLUDED_CUSTOMMODULE_READTAGS_IMPL_H

#include <gnuradio/customModule/ReadTags.h>
#include <string>
using namespace std;
namespace gr {
namespace customModule {

class ReadTags_impl : public ReadTags
{
private:
    std::vector<gr_complex> ctaps;
    std::vector<int> index;
    std::vector<int> ind;
    const pmt::pmt_t ctaps_out;
public:
    ReadTags_impl(std::string tag_key);
    ~ReadTags_impl() override;
    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_READTAGS_IMPL_H */
