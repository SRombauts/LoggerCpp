/**
 * @file    OutputSyslog.cpp
 * @ingroup LoggerCpp
 * @brief   Output to Unix syslog
 * @author  andre
 *
 * Copyright (c) 2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifdef __unix__

#include <LoggerCpp/OutputSyslog.h>
#include <syslog.h>
#include <assert.h>

namespace Log {

OutputSyslog::OutputSyslog(const Config::Ptr& aConfigPtr) {
    assert(aConfigPtr);

    mLogname = aConfigPtr->get("syslogname", "LoggerCpp");
    openlog(mLogname.c_str(), LOG_CONS, LOG_USER);
}

OutputSyslog::~OutputSyslog() {
    closelog();
}


// Output the Log to the standard console using printf
void OutputSyslog::output(const Channel::Ptr& aChannelPtr, const Log& aLog) const {

    // Just in case you wondered. No time stamp is needed here. Syslog will take care of it.

    // Now transform internal severity to syslog severity
    int pri = LOG_DEBUG;
    switch (aLog.getSeverity()) {
        default:
        case Log::eDebug:   pri = LOG_DEBUG;    break;
        case Log::eInfo:    pri = LOG_INFO;     break;
        case Log::eNotice:  pri = LOG_NOTICE;   break;
        case Log::eWarning: pri = LOG_WARNING;  break;
        case Log::eError:   pri = LOG_ERR;      break;
        case Log::eCritic:  pri = LOG_CRIT;     break;
    }

    // Now write it out to syslog
    syslog(pri, "%-12s %s %s\n",
           aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()),
           (aLog.getStream()).str().c_str());
}


} // namespace Log

#endif // __unix__
