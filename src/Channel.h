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


/**
 * @brief   The named channel shared by Logger objects using the same name
 */
struct Channel
{
    friend class Logger;

public:
    /// @brief Shared Pointer to a Channel
    typedef shared_ptr<Channel> Ptr;

public:
    // Constructor, and non virtual destructor
    Channel(const char* apName, Log::Level aLevel = Log::eDebug);
    ~Channel(void);

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

    // To be used only by the Logger class
    void output(const Log& aLog) const;

    static const char* toString (Log::Level aLevel);

private:
    std::string mName;  //!< Name of the Channel
    Log::Level  mLevel; //!< Current Log::Level of the Channel
};

