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


/**
 * @brief Construct a RAII (private) log object for the Logger class
*/
Log::Log(const Logger& aLogger, Level aSeverity) :
    mLogger(aLogger),
    mSeverity(aSeverity),
    mpStream(NULL)
{
    // Construct a stream only if the severity of the Log is above its Logger level
    if (aSeverity >= aLogger.mLevel)
    {
        mpStream = new(std::ostringstream);
    }
}


/**
 * @brief Output the Log string stream
*/
Log::~Log(void)
{
    if (NULL != mpStream) {
        mLogger.output(*this);

        delete mpStream;
        mpStream = NULL;
    }
}
