/**
 * @file    Log.cpp
 * @brief   A RAII log object constructed by the Logger class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Log.h"
#include "Logger.h"


Log::Log(Logger& aLogger, Level aSeverity, bool abIsActive) :
    mLogger(aLogger),
    mSeverity(aSeverity),
    mpStream(NULL)
{
    if (abIsActive) {
        mpStream = new(std::ostringstream);
    }
}

Log::~Log(void)
{
    if (NULL != mpStream) {
        mLogger.print(*this);

        delete mpStream;
        mpStream = NULL;
    }

}


Log& Log::test(const char* apText)
{
    if (NULL != mpStream) {
        *mpStream << apText;
    }
    return (*this);
}
