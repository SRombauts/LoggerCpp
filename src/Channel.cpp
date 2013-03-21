/**
 * @file    Channel.cpp
 * @ingroup LoggerCpp
 * @brief   A simple thread-safe Channel class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Channel.h"

#include <iostream>
#include <cstdio>
#include <cassert>
#include <ctime>


/**
 * @brief Initialize a Channel utility object
 *
 * @param[in] apChannelName    String to identify origin of Log output by this Channel
 * @param[in] aChannelLevel    The minimum level of severity from which to output Log
 */
Channel::Channel(const char* apChannelName, Log::Level aChannelLevel /* = eDebug */) :
    mName(apChannelName),
    mLevel(aChannelLevel)
{
}

Channel::~Channel(void)
{
}



/**
 * @brief Output the Log. Used by the Log class destructor.
 *
 * @param[in] aLog  The Log to output
 *
 * @todo redirect the Log to a LogManager class
 * @todo the LogManager class will dispatch it to LogOutputMemory/LogOutputConsole/LogOutputFile
 */
void Channel::output(const Log& aLog) const
{
    time_t datetime;
    time(&datetime);
    struct tm* timeinfo = localtime(&datetime);
    assert (NULL != timeinfo);

    // uses fprintf for atomic thread-safe operation
    fprintf(stdout, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u  %-20s %s  %s\n",
            (timeinfo->tm_year+1900), timeinfo->tm_mon, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            mName.c_str(), toString(aLog.GetSeverity()), (aLog.GetStream()).str().c_str());
    fflush(stdout);
}


/**
 * @brief Level to String conversion
 *
 * @todo remove duplicate
*/
const char* Channel::toString (Log::Level aLevel)
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
