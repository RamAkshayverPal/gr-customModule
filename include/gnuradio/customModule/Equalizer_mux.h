/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_EQUALIZER_MUX_H
#define INCLUDED_CUSTOMMODULE_EQUALIZER_MUX_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API Equalizer_mux : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<Equalizer_mux> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of customModule::Equalizer_mux.
     *
     * To avoid accidental use of raw pointers, customModule::Equalizer_mux's
     * constructor is in a private implementation
     * class. customModule::Equalizer_mux::make is the public interface for
     * creating new instances.
     */
    static sptr make(int Vectorsize = 64);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_EQUALIZER_MUX_H */
