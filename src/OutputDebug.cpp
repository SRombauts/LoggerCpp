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

#include <cstdio>


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
    const Time&         time = aLog.getTime();
    char                buffer[256];

    // uses snprintf for atomic thread-safe operation
    _snprintf(buffer, 256, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u  %-20s %s  %s\n",
            time.year, time.month, time.day,
            time.hour, time.minute, time.second, time.ms,
            aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()), (aLog.getStream()).str().c_str());
    buffer[255] = '\0';
    OutputDebugStringA(buffer);
}


} // namespace Log

#endif  // WIN32
