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

#include "Log.h"
#include "Logger.h"


namespace Log
{


// Construct a RAII (private) log object for the Logger class
Log::Log(const Logger& aLogger, Level aSeverity) :
    mLogger(aLogger),
    mSeverity(aSeverity),
    mpStream(NULL)
{
    // Construct a stream only if the severity of the Log is above its Logger Log::Level
    if (aSeverity >= aLogger.getLevel ()) {
        mpStream = new(std::ostringstream);
    }
}

// Destructor : output the Log string stream
Log::~Log(void)
{
    if (NULL != mpStream) {
        mTime.make();
        mLogger.output(*this);

        delete mpStream;
        mpStream = NULL;
    }
}

// Convert a Level to its string representation
const char* Log::toString (Log::Level aLevel)
{
    const char* pString = NULL;

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


} // namespace Log
