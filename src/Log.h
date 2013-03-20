/**
 * @file    Log.h
 * @ingroup LoggerCpp
 * @brief   A RAII (private) log object constructed by the Logger class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <sstream>
#include <iomanip>

// forward declaration
class Logger;


/**
 * @brief   A RAII (private) log object constructed by the Logger class
 *
 * This represents a full line of log, at a certain level of severity.
 *
 * It is constructed and initialized by a call to Logger::debug(),
 * Logger::info(), ... or Logger::critic().
 * Is is then used by successive stream call "<<", and is naturally terminated
 * by it destructor at the end of the line, calling the Logger::output() method.
 *
 * It contains all required information for further formating, printing and transmitting
 * by the Logger class.
 */
class Log
{
    friend class Logger;

public:
    /**
     * @brief Enumeration of the severity levels
     */
    enum Level {
        eDebug = 0,
        eInfo,
        eNotice,
        eWarning,
        eError,
        eCritic
    };

public:
    // Output stream operator
    template <typename T>
    Log& operator<< (const T& aValue)
    {
        if (NULL != mpStream) {
            *mpStream << aValue;
        }
        return (*this);
    }

    // Public non virtual destructor
    ~Log(void);

private:
    // Private constructor, reserved for the Logger class
    Log(const Logger& aLogger, Level aSeverity);

    /// @{ Non-copyable object
    Log(const Log&);
    void operator=(const Log&);
    /// @}

private:
   const Logger&        mLogger;    //!< Reference to the parent Logger
   Level                mSeverity;  //!< Severity of this Log
   std::ostringstream*  mpStream;   //!< The underlying string stream
};

