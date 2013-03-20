/**
 * @file    Logger.h
 * @ingroup LoggerCpp
 * @brief   A simple thread-safe Logger class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Log.h"

#include <string>

/**
 * @brief   A simple thread-safe logger class
 *
 * This Logger is designed to be easy to use and efficient.
 * It can be used as a member variable, and will not consume much cpu
 * if the log severity is below the Logger current level.
 *
 * @todo Move mName and mLevel to a mChannelPtr returned by the LogManager
 */
class Logger
{
    friend class Log;

public:
    // Constructor, and non virtual destructor
    Logger(const char* apName, Log::Level aLevel = Log::eDebug);
    ~Logger(void);

    // Utility const method to produce Log objets, used to collect the stream to output
    Log debug(void) const;
    Log info(void) const;
    Log notice(void) const;
    Log warning(void) const;
    Log error(void) const;
    Log critic(void) const;

    inline void setLevel (Log::Level aLevel) {
        mLevel = aLevel;
    }

    inline std::string& getName () {
        return mName;
    }

private:
    /// @{ Non-copyable object
    Logger(Logger&);
    void operator=(Logger&);
    /// @}

    // To be used only by the Log class
    void output(const Log& aLog) const;

    static const char* toString (Log::Level aLevel);

private:
    std::string mName;  //!< Name of the LogChannel
    Log::Level  mLevel; //!< Current severity level of the LogChannel
};

