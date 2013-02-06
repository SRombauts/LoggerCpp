/**
 * @file    Logger.cpp
 * @brief   A simple thread-safe Logger class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Logger.h"

#include <iostream>
#include <cstdio>
#include <cassert>
#include <ctime>


/**
 * @brief Initialize a Logger utility object
 *
 * @param[in] apName    String to identify origin of Log output by this Logger
 * @param[in] aLevel    The minimum level of severity from which to output Log
 */
Logger::Logger(const char* apName, Log::Level aLevel /* = eDebug */) :
    mName(apName),
    mLevel(aLevel)
{
}

Logger::~Logger(void)
{
}


// Utility const method to produce Log objets, used to collect the stream to output
Log Logger::debug(void) const
{
    return Log(*this, Log::eDebug);
}
Log Logger::info(void) const
{
    return Log(*this, Log::eInfo);
}
Log Logger::notice(void) const
{
    return Log(*this, Log::eNotice);
}
Log Logger::warning(void) const
{
    return Log(*this, Log::eWarning);
}
Log Logger::error(void) const
{
    return Log(*this, Log::eError);
}
Log Logger::critic(void) const
{
    return Log(*this, Log::eCritic);
}


// To be used only by Log class
void Logger::output(const Log& aLog) const
{
    struct tm* timeinfo = localtime(&aLog.mTime);
    assert (NULL != timeinfo);

    // uses fprintf for atomic thread-safe operation
    fprintf(stdout, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u  %-20s %s  %s\n",
            (timeinfo->tm_year+1900), timeinfo->tm_mon, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            mName.c_str(), toString(aLog.mSeverity), (*aLog.mpStream).str().c_str());
    fflush(stdout);
}


// Level to String conversion
const char* Logger::toString (Log::Level aLevel)
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
