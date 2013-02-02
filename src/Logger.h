/**
 * @file    Logger.h
 * @brief   A simple Logger class
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
 * @brief   A simple logger class
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

    Log debug(void);
    Log info(void);
    Log notice(void);
    Log warning(void);
    Log error(void);
    Log crash(void);

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
    void print(const Log& aLog);

    static const char* toString (Log::Level aLevel);

private:
    std::string mName;
    Log::Level  mLevel;
};

