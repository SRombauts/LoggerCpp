/**
 * @file    Logger.cpp
 * @brief   A simple Logger class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Logger.h"

#include <iostream>


Logger::Logger(const char* apName, Log::Level aLevel /* = eDebug */) :
    mName(apName),
    mLevel(aLevel)
{
    std::cout << "Logger(" << mName.c_str() << ")" << std::endl;
}

Logger::~Logger(void)
{
    std::cout << "~Logger(" << mName.c_str() << ")" << std::endl;
}


Log Logger::debug(void)
{
    Log log(*this, Log::eDebug, (Log::eDebug >= mLevel));
    return log;
}
Log Logger::info(void)
{
    Log log(*this, Log::eInfo, (Log::eInfo >= mLevel));
    return log;
}
Log Logger::notice(void)
{
    Log log(*this, Log::eNotice, (Log::eNotice >= mLevel));
    return log;
}
Log Logger::warning(void)
{
    Log log(*this, Log::eWarning, (Log::eWarning >= mLevel));
    return log;
}
Log Logger::error(void)
{
    Log log(*this, Log::eError, (Log::eError >= mLevel));
    return log;
}
Log Logger::crash(void)
{
    Log log(*this, Log::eCrash, (Log::eCrash >= mLevel));
    return log;
}


// To be used only for Log class
void Logger::print(const Log& aLog)
{
    // TODO SRombauts use printf or fprintf and fflush for thread-safety
    std::cout << mName.c_str() << "\t"
              << toString(aLog.mSeverity) << "\t"
              << (*(aLog.mpStream)).str() << std::endl;
}


const char* Logger::toString (Log::Level aLevel)
{
    const char* pString = NULL;

    switch (aLevel) {
    case Log::eDebug:   pString = "DBUG"; break;
    case Log::eInfo:    pString = "INFO"; break;
    case Log::eNotice:  pString = "NOTE"; break;
    case Log::eWarning: pString = "WARN"; break;
    case Log::eError:   pString = "EROR"; break;
    case Log::eCrash:   pString = "CRSH"; break;
    default:            pString = "????"; break;
    }

    return pString;
}
