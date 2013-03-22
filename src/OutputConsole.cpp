/**
 * @file    OutputConsole.cpp
 * @ingroup LoggerCpp
 * @brief   Output to the standard console using fprintf() with stdout
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "OutputConsole.h"

#include <iostream>
#include <cstdio>
#include <cassert>
#include <ctime>


namespace Log
{

OutputConsole::OutputConsole(const Config::Ptr& aConfigPtr)
{
}

OutputConsole::~OutputConsole()
{
}

/**
 * @brief Output the Log to the standard console using printf
 *
 * @param[in] aChannelPtr   The underlying Channel of the Log
 * @param[in] aLog          The Log to output
 */
void OutputConsole::output(const Channel::Ptr& aChannelPtr, const Log& aLog) const
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


} // namespace Log
