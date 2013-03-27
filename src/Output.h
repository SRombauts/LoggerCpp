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

#include "Channel.h"

#include <vector>
#include <typeinfo>

// This includes "boost/shared_ptr.hpp" if LOGGER_USE_BOOST_SHARED_PTR is defined,
// or <memory> (or <tr1/memory>) when C++11 (or experimental C++0x) is available,
// or a custom minimal shared_ptr implementation,
// and imports the "shared_ptr" symbol inside the Log namespace (ie. Log::shared_ptr)
#include "shared_ptr.hpp"


namespace Log
{


// Forward declaration
class Log;

/**
 * @brief   Interface of an Output
 * @ingroup LoggerCpp
 */
class Output
{
public:
   /// @brief Virtual destructor
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
