/**
 * @file    Output.h
 * @ingroup LoggerCpp
 * @brief   Interface of an Output
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Log.h"
#include "Channel.h"

#include <vector>


/// @todo try first for the C++11 std::shared_ptr, or the minimal shared_ptr implementation
#include <boost/shared_ptr.hpp>
#define shared_ptr  boost::shared_ptr


namespace Log
{


/**
 * @brief   Interface of an Output
 * @ingroup LoggerCpp
 */
class Output
{
public:
   virtual ~Output() {}

public:
    /// @brief Shared Pointer to an Output
    typedef shared_ptr<Output>  Ptr;
    /// @brief List of Output objects
    typedef std::vector<Ptr>    Vector;

    /**
     * @brief Output the Log
     *
     * @param[in] aChannelPtr   The underlying Channel of the Log
     * @param[in] aLog          The Log to output
     */
    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const = 0;

    /// @brief Return the type name of the Output object
    inline const char* name() const {
        return typeid(this).name();
    }

};


} // namespace Log
