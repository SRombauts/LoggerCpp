/**
 * @file    Time.cpp
 * @ingroup LoggerCpp
 * @brief   Current time precise to the millisecond.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Time.h"

#ifdef WIN32
#include <windows.h>
#else
#include <time.h>
#include <sys/time.h>
#endif

namespace Log
{


/// @todo Set to current time
Time::Time(void)
{
#ifdef WIN32
    SYSTEMTIME now;
    GetLocalTime(&now);
#else
    struct timeval now;
    gettimeofday(&now, NULL);
    struct tm* timeinfo = localtime(&now);
#endif
}


} // namespace Log
