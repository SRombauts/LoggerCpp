/**
 * @file    Log.cpp
 * @ingroup LoggerCpp
 * @brief   A RAII (private) log object constructed by the Logger class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <LoggerCpp/Log.h>
#include <LoggerCpp/Logger.h>

#include <cstring>


namespace Log {


// Construct a RAII (private) log object for the Logger class
Log::Log(const Logger& aLogger, Level aSeverity) :
    mLogger(aLogger),
    mSeverity(aSeverity),
    mpStream(nullptr) {
    // Construct a stream only if the severity of the Log is above its Logger Log::Level
    if (aSeverity >= aLogger.getLevel()) {
        mpStream = new(std::ostringstream);
    }
}

// Destructor : output the Log string stream
Log::~Log(void) {
    if (nullptr != mpStream) {
        mTime.make();
        mLogger.output(*this);

        delete mpStream;
        mpStream = nullptr;
    }
}

// Convert a Level to its string representation
const char* Log::toString(Log::Level aLevel) {
    const char* pString = nullptr;

    switch (aLevel) {
        case Log::eDebug:   pString = "DBUG"; break;
        case Log::eInfo:    pString = "INFO"; break;
        case Log::eNotice:  pString = "NOTE"; break;
        case Log::eWarning: pString = "WARN"; break;
        case Log::eError:   pString = "EROR"; break;
        case Log::eCritic:  pString = "CRIT"; break;
        default:            pString = "????"; break;
    }

    return pString;
}

// Convert a string representation of a Level to its corresponding value
Log::Level Log::toLevel(const char* apLevel) {
    Log::Level level;

    if      (0 == strncmp(apLevel, "DBUG", 4))  level = Log::eDebug;
    else if (0 == strncmp(apLevel, "INFO", 4))  level = Log::eInfo;
    else if (0 == strncmp(apLevel, "NOTE", 4))  level = Log::eNotice;
    else if (0 == strncmp(apLevel, "WARN", 4))  level = Log::eWarning;
    else if (0 == strncmp(apLevel, "EROR", 4))  level = Log::eError;
    else /* (0 == strncmp(apLevel, "CRIT", 4)*/ level = Log::eCritic;   // NOLINT(whitespace/newline)

    return level;
}


} // namespace Log
