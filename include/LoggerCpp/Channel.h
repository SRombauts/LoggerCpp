/**
 * @file    Channel.h
 * @ingroup LoggerCpp
 * @brief   The named channel shared by Logger objects using the same name
 *
 * Copyright (c) 2013-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <LoggerCpp/Log.h>

#include <map>
#include <string>

// The following includes "boost/shared_ptr.hpp" if LOGGER_USE_BOOST_SHARED_PTR is defined,
// or <memory> (or <tr1/memory>) when C++11 (or experimental C++0x) is available,
// or a custom minimal shared_ptr implementation,
// and imports the "shared_ptr" symbol inside the Log namespace (ie. Log::shared_ptr)
#include <LoggerCpp/shared_ptr.hpp>


namespace Log {


/**
 * @brief   The named channel shared by Logger objects using the same name
 * @ingroup LoggerCpp
 *
 *  A Channel is the underlying object used by one or many Logger objects to
 * associate a named prefix and an output Log::Level.
 * Sharing a same Channel between multiple Logger enable changing the
 * Level of many Logger objects at once.
 */
class Channel {
public:
    /// @brief Shared Pointer to a Channel object
    typedef shared_ptr<Channel>         Ptr;
    /// @brief Map of shared pointer of Channel objects
    typedef std::map<std::string, Ptr>  Map;

public:
    /**
     * @brief Initialize a named Channel
     *
     * @param[in] apChannelName    String to identify origin of Log output by this Channel
     * @param[in] aChannelLevel    The default minimum Log::Level of severity from which to output Log
     */
    Channel(const char* apChannelName, Log::Level aChannelLevel) :
        mName(apChannelName),
        mLevel(aChannelLevel)
    {}

    /// @brief Non virtual destructor
    ~Channel(void) {
    }

    /// @brief Name of the Channel
    inline const std::string& getName(void) const {
        return mName;
    }

    /// @brief Set the current output Log::Level of the Channel
    inline void setLevel(Log::Level aLevel) {
        mLevel = aLevel;
    }

    /// @brief Current Log::Level of the Channel
    inline Log::Level getLevel(void) const {
        return mLevel;
    }

private:
    /// @{ Non-copyable object
    Channel(Channel&);
    void operator=(Channel&);
    /// @}

private:
    std::string mName;  ///< Name of the Channel
    Log::Level  mLevel; ///< Current Log::Level of the Channel
};


} // namespace Log
