/**
 * @file    Manager.cpp
 * @ingroup LoggerCpp
 * @brief   The static class that manage the registered channels and outputs
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Manager.h"

#include <iostream>
#include <cstdio>
#include <cassert>
#include <ctime>


Manager::ChannelMap Manager::mChannelMap;


/**
 * @brief Return the Channel corresponding to the provided name
 *
 * Create a new Channel or get the existing one. 
 *
 * @param[in] apChannelName String to identify the underlying Channel of a Logger
*/
Channel::Ptr Manager::get(const char* apChannelName)
{
    Channel::Ptr            ChannelPtr;
    ChannelMap::iterator    iChannelPtr = mChannelMap.find(apChannelName);

    if (mChannelMap.end() != iChannelPtr) {
        ChannelPtr = iChannelPtr->second;
    } else {
        ChannelPtr.reset(new Channel(apChannelName));
        mChannelMap[apChannelName] = ChannelPtr;
    }

    return ChannelPtr;
}

/**
 * @brief Output the Log to all the active Output objects.
 *
 * @param[in] aChannelPtr   The underlying Channel of the Log
 * @param[in] aLog          The Log to output
 *
 * @todo the LogManager class will dispatch it to LogOutputConsole/LogOutputFile/LogOutputVS/LogOutputMemory/
 */
void Manager::output(const Channel::Ptr& aChannelPtr, const Log& aLog)
{
    time_t datetime;
    time(&datetime);
    struct tm* timeinfo = localtime(&datetime);
    assert (NULL != timeinfo);

    // uses fprintf for atomic thread-safe operation
    fprintf(stdout, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u  %-20s %s  %s\n",
            (timeinfo->tm_year+1900), timeinfo->tm_mon, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()), (aLog.getStream()).str().c_str());
    fflush(stdout);
}

