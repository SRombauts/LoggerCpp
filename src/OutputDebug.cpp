/**
 * @file    OutputDebug.cpp
 * @ingroup LoggerCpp
 * @brief   Output to the Visual Studio debugger using OutputDebugString()
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifdef WIN32

#include "OutputDebug.h"

#include <Windows.h>

#include <iostream>
#include <cstdio>
#include <cassert>
#include <ctime>


namespace Log
{

OutputDebug::OutputDebug(const Config::Ptr& aConfigPtr)
{
}

OutputDebug::~OutputDebug()
{
}

/**
 * @brief Output the Log to the Visual Studio debugger using OutputDebugString()
 *
 * @param[in] aChannelPtr   The underlying Channel of the Log
 * @param[in] aLog          The Log to output
 */
void OutputDebug::output(const Channel::Ptr& aChannelPtr, const Log& aLog) const
{
    char buffer[256];
    time_t datetime;
    time(&datetime);
    struct tm* timeinfo = localtime(&datetime);
    assert (NULL != timeinfo);

    std::string log = aLog.getStream().str();

    // uses fprintf for atomic thread-safe operation
    _snprintf(buffer, 256, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u  %-20s %s  %s\n",
            (timeinfo->tm_year+1900), timeinfo->tm_mon, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()), (aLog.getStream()).str().c_str());
    buffer[255] = '\0';
    OutputDebugStringA(buffer);
}


} // namespace Log

#endif  // WIN32
