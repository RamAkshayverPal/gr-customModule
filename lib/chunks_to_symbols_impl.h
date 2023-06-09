/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_CHUNKS_TO_SYMBOLS_IMPL_H
#define INCLUDED_CUSTOMMODULE_CHUNKS_TO_SYMBOLS_IMPL_H

#include <gnuradio/customModule/chunks_to_symbols.h>
#include <pmt/pmt.h>

namespace gr {
namespace customModule {

template <class IN_T, class OUT_T>
class chunks_to_symbols_impl : public chunks_to_symbols<IN_T, OUT_T>
{
private:
    const unsigned int d_D;
    std::vector<OUT_T> d_symbol_table;
    const pmt::pmt_t symbol_table_key;

public:
    chunks_to_symbols_impl(const std::vector<OUT_T>& symbol_table,
                           const unsigned int D = 1);

    ~chunks_to_symbols_impl() override;

    void handle_set_symbol_table(const pmt::pmt_t& symbol_table_pmt);
    void set_symbol_table(const std::vector<OUT_T>& symbol_table) override;

    unsigned int D() const override { return d_D; }
    std::vector<OUT_T> symbol_table() const override { return d_symbol_table; }

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

    bool check_topology(int ninputs, int noutputs) override
    {
        return ninputs == noutputs;
    }
};

} /* namespace customModule */
} /* namespace gr */

#endif /* CHUNKS_TO_SYMBOLS_IMPL_H */
