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

#include <cstdio>


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
    const Time& time = aLog.getTime();

    // uses fprintf for atomic thread-safe operation
    fprintf(stdout, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u  %-20s %s  %s\n",
            time.year, time.month, time.day,
            time.hour, time.minute, time.second, time.ms,
            aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()), (aLog.getStream()).str().c_str());
    fflush(stdout);
}


} // namespace Log
