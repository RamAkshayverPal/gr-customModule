/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_CHUNKS_TO_SYMBOLS_H
#define INCLUDED_CUSTOMMODULE_CHUNKS_TO_SYMBOLS_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_interpolator.h>
#include <cstdint>

namespace gr {
namespace customModule {

/*!
 * \brief Map a stream of unpacked symbol indexes to stream of
 * float or complex constellation points in D dimensions (D = 1 by
 * default) \ingroup converter_blk
 *
 * \details
 * \li input: stream of IN_T
 * \li output: stream of OUT_T
 *
 * \li out[n D + k] = symbol_table[in[n] D + k], k=0,1,...,D-1
 *
 * The combination of gr::blocks::packed_to_unpacked_XX followed
 * by gr::customModule::chunks_to_symbols_XY handles the general case
 * of mapping from a stream of bytes or shorts into arbitrary
 * float or complex symbols.
 *
 * \sa gr::blocks::packed_to_unpacked_bb, gr::blocks::unpacked_to_packed_bb,
 * \sa gr::blocks::packed_to_unpacked_ss, gr::blocks::unpacked_to_packed_ss,
 * \sa gr::customModule::chunks_to_symbols_bf, gr::customModule::chunks_to_symbols_bc.
 * \sa gr::customModule::chunks_to_symbols_sf, gr::customModule::chunks_to_symbols_sc.
 */
template <class IN_T, class OUT_T>
class CUSTOMMODULE_API chunks_to_symbols : virtual public sync_interpolator
{
public:
    typedef std::shared_ptr<chunks_to_symbols<IN_T, OUT_T>> sptr;

    /*!
     * Make a chunks-to-symbols block.
     *
     * \param symbol_table: list that maps chunks to symbols.
     * \param D: dimension of table.
     */
    static sptr make(const std::vector<OUT_T>& symbol_table, const unsigned int D = 1);

    virtual unsigned int D() const = 0;
    virtual std::vector<OUT_T> symbol_table() const = 0;
    virtual void set_symbol_table(const std::vector<OUT_T>& symbol_table) = 0;
};

typedef chunks_to_symbols<std::uint8_t, float> chunks_to_symbols_bf;
typedef chunks_to_symbols<std::uint8_t, gr_complex> chunks_to_symbols_bc;
typedef chunks_to_symbols<std::int16_t, float> chunks_to_symbols_sf;
typedef chunks_to_symbols<std::int16_t, gr_complex> chunks_to_symbols_sc;
typedef chunks_to_symbols<std::int32_t, float> chunks_to_symbols_if;
typedef chunks_to_symbols<std::int32_t, gr_complex> chunks_to_symbols_ic;
} /* namespace customModule */
} /* namespace gr */

#endif /* CHUNKS_TO_SYMBOLS_H */
