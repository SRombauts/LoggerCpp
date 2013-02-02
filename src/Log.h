/**
 * @file    Log.h
 * @brief   A RAII log object constructed by the Logger class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <sstream>

// forward declaration
class Logger;


/**
 * @brief   A RAII log object constructed by the Logger class
 *
 * @author  02/02/2013 SRombauts
 */
class Log
{
    friend class Logger;

public:
    enum Level {
        eDebug = 0,
        eInfo,
        eNotice,
        eWarning,
        eError,
        eCrash
    };

public:
    Log& test(const char* apText);

    // Public non virtual destructor
    ~Log(void);

private:
    // Private constructor, reserved for the Logger class
    Log(Logger& aLogger, Level aSeverity, bool abIsActive);

    /// @{ Non-copyable object
    Log(Log&);
    void operator=(Log&);
    /// @}

private:
   Logger&              mLogger;
   Level                mSeverity;
   std::ostringstream*  mpStream;
};

