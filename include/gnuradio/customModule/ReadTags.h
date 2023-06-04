/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_READTAGS_H
#define INCLUDED_CUSTOMMODULE_READTAGS_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API ReadTags : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<ReadTags> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of customModule::ReadTags.
     *
     * To avoid accidental use of raw pointers, customModule::ReadTags's
     * constructor is in a private implementation
     * class. customModule::ReadTags::make is the public interface for
     * creating new instances.
     */
    static sptr make(std::string tag_key = "ofdm_sync_chan_taps");
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_READTAGS_H */
