/**
 * @file    Logger.h
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
 *
 *
 * @author  2013/02/02 SRombauts
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

    // To be used only for Log class
    void output(const Log& aLog) const;

    static const char* toString (Log::Level aLevel);

private:
    std::string mName;
    Log::Level  mLevel;
};

