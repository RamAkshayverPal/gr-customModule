/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_OFDM_FRAME_EQUAL_VCVC_H
#define INCLUDED_CUSTOMMODULE_OFDM_FRAME_EQUAL_VCVC_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/tagged_stream_block.h>
#include <gnuradio/customModule/ofdm_equalizer_base.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API ofdm_frame_equal_vcvc : virtual public gr::tagged_stream_block
{
public:
    typedef std::shared_ptr<ofdm_frame_equal_vcvc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of
     * customModule::ofdm_frame_equal_vcvc.
     *
     * To avoid accidental use of raw pointers, customModule::ofdm_frame_equal_vcvc's
     * constructor is in a private implementation
     * class. customModule::ofdm_frame_equal_vcvc::make is the public interface for
     * creating new instances.
     */
    static sptr make(ofdm_equalizer_base::sptr equalizer,
                     int cp_len,
                     const std::string& len_tag_key,
                     bool propagate_channel_state,
                     int fixed_frame_len);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_OFDM_FRAME_EQUAL_VCVC_H */
