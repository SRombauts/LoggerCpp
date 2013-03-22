/**
 * @file    Channel.h
 * @ingroup LoggerCpp
 * @brief   The named channel shared by Logger objects using the same name
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Log.h"

#include <string>

/// @todo try first for the C++11 std::shared_ptr, or the minimal shared_ptr implementation
#include <boost/shared_ptr.hpp>
#define shared_ptr  boost::shared_ptr


namespace Log
{


/**
 * @brief   The named channel shared by Logger objects using the same name
 */
class Channel
{
public:
    /// @brief Shared Pointer to a Channel
    typedef shared_ptr<Channel> Ptr;

public:
    /**
     * @brief Initialize a nammed Channel
     *
     * @param[in] apChannelName    String to identify origin of Log output by this Channel
     * @param[in] aChannelLevel    The default minimum Log::Level of severity from which to output Log
     */
    Channel(const char* apChannelName, Log::Level aChannelLevel = Log::eDebug) :
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
    inline void setLevel (Log::Level aLevel) {
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
    std::string mName;  //!< Name of the Channel
    Log::Level  mLevel; //!< Current Log::Level of the Channel
};


} // namespace Log
