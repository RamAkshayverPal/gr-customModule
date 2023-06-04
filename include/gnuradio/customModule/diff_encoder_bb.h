/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_DIFF_ENCODER_BB_H
#define INCLUDED_CUSTOMMODULE_DIFF_ENCODER_BB_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/customModule/diff_coding_type.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API diff_encoder_bb : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<diff_encoder_bb> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of customModule::diff_encoder_bb.
     *
     * To avoid accidental use of raw pointers, customModule::diff_encoder_bb's
     * constructor is in a private implementation
     * class. customModule::diff_encoder_bb::make is the public interface for
     * creating new instances.
     */
    static sptr make(unsigned int modulus,
                     enum diff_coding_type coding = DIFF_DIFFERENTIAL);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_DIFF_ENCODER_BB_H */
