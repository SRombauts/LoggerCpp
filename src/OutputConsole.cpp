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

#include "LoggerCpp/OutputConsole.h"

#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Log {


// Constructor
OutputConsole::OutputConsole(const Config::Ptr& aConfigPtr) {
    (void)aConfigPtr;
}

// Destructor
OutputConsole::~OutputConsole() {
}

#ifdef _WIN32

// Convert a Level to a Win32 console color text attribute
unsigned short OutputConsole::toWin32Attribute(Log::Level aLevel) {
    unsigned short code;

    switch (aLevel) {
        case Log::eDebug    : code = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break; // white
        case Log::eInfo     : code = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
        case Log::eNotice   : code = FOREGROUND_GREEN;                                    break; // green
        case Log::eWarning  : code = FOREGROUND_RED | FOREGROUND_GREEN;                   break; // orange
        case Log::eError    : code = FOREGROUND_RED;                                      break; // red
        case Log::eCritic   : code = FOREGROUND_RED | FOREGROUND_INTENSITY;               break; // light red
        default             : code = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break; // white
    }

    return (code);
}

#else // _WIN32

// Convert a Level to its ANSI escape color code
unsigned int OutputConsole::toEscapeCode(Log::Level aLevel) {
    unsigned int code;

    switch (aLevel) {
        case Log::eDebug:   code = 34; break;   // 34=blue
        case Log::eInfo:    code = 39; break;   // 39=white
        case Log::eNotice:  code = 32; break;   // 32=green
        case Log::eWarning: code = 33; break;   // 33=orange
        case Log::eError:   code = 31; break;   // 31=red
        case Log::eCritic:  code = 95; break;   // 95=magenta
        default:            code = 39; break;   // 39=white (reset to default)
    }

    return code;
}

#endif // _WIN32

// Output the Log to the standard console using fprintf
void OutputConsole::output(const Channel::Ptr& aChannelPtr, const Log& aLog) const {
    const DateTime& time = aLog.getTime();

    // uses fprintf for atomic thread-safe operation
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), toWin32Attribute(aLog.getSeverity()));
    fprintf(stdout, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u  %-12s %s %s\n",
#else  // _WIN32
    fprintf(stdout, "\x1B[%02um%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u  %-12s %s %s\x1b[39m\n",
            toEscapeCode(aLog.getSeverity()),
#endif // _WIN32
            time.year, time.month, time.day,
            time.hour, time.minute, time.second, time.ms,
            aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()), (aLog.getStream()).str().c_str());
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif // _WIN32
    fflush(stdout);
}


} // namespace Log
