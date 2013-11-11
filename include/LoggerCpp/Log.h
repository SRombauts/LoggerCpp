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

#include "LoggerCpp/DateTime.h"

#include <sstream>
#include <iomanip>  // For easy use of parametric manipulators (setfill, setprecision) by client code


namespace Log {


// forward declaration
class Logger;


/**
 * @brief   A RAII (private) log object constructed by the Logger class
 * @ingroup LoggerCpp
 *
 * a Log represents a full line of log, at a certain Log::Level of severity.
 *
 * It is constructed and initialized by a call to Logger::debug(),
 * Logger::info(), ... or Logger::critic().
 * Is is then used by successive stream call "<<", and is naturally terminated
 * by it destructor at the end of the line, calling the Logger::output() method.
 *
 * It contains all required information for further formating, printing and transmitting
 * by the Logger class.
 */
class Log {
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
    /**
     * @brief stream inserter operator
     *
     * @param[in] aValue    Value to be formatted and inserted into the Log string stream
     *
     * @return Currents Log instance 
     */
    template <typename T>
    Log& operator<< (const T& aValue) {
        if (NULL != mpStream) {
            *mpStream << aValue;
        }
        return (*this);
    }

    /**
     * @brief Destructor : output the Log string stream
     */
    ~Log(void);

    /// @brief Severity Level of this Log
    inline Level getSeverity(void) const {
        return mSeverity;
    }

    /// @brief Timestamp of this Log
    inline const DateTime& getTime(void) const {
        return mTime;
    }

    /// @brief The underlying string stream
    inline const std::ostringstream& getStream(void) const {
        return *mpStream;
    }

    /**
     * @brief Convert a Level to its string representation
     *
     * @param[in] aLevel Log severity Level to convert
     *
     * @return Severity Level Description
     *
     * @todo stringToLevel()
     */
    static const char* toString(Log::Level aLevel);

private:
    /**
     * @brief Construct a RAII (private) log object for the Logger class
     *
     * @param[in] aLogger   Reference to the parent Logger
     * @param[in] aSeverity Severity of this Log
     */
    Log(const Logger& aLogger, Level aSeverity);

    /// @{ Non-copyable object
    Log(const Log&);
    void operator=(const Log&);
    /// @}

private:
    const Logger&       mLogger;    ///< Reference to the parent Logger
    Level               mSeverity;  ///< Severity of this Log
    DateTime                mTime;      ///< Timestamp of the output
    std::ostringstream* mpStream;   ///< The underlying string stream
};


} // namespace Log

