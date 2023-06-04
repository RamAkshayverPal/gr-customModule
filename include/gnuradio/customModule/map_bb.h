/* -*- c++ -*- */
/*
 * Copyright 2023 Ram Akshayver Pal.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_MAP_BB_H
#define INCLUDED_CUSTOMMODULE_MAP_BB_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API map_bb : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<map_bb> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of customModule::map_bb.
     *
     * To avoid accidental use of raw pointers, customModule::map_bb's
     * constructor is in a private implementation
     * class. customModule::map_bb::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::vector<int>& map);
    virtual void set_map(const std::vector<int>& map) = 0;
    virtual std::vector<int> map() const = 0;
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_MAP_BB_H */
