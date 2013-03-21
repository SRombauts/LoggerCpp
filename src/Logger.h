/**
 * @file    Logger.h
 * @ingroup LoggerCpp
 * @brief   A simple thread-safe Logger class
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Log.h"
#include "Channel.h"

#include <string>

/**
 * @brief   A simple thread-safe logger class
 *
 * This Logger is designed to be easy to use and efficient.
 * It can be used as a member variable, and will not consume much CPU
 * if the log severity is below the Logger current level.
 *
 * @note A Logger object is copyable without any limitations
 *
 * @todo Move mName and mLevel to a mChannelPtr returned by the LogManager
 */
class Logger
{
    friend class Log;

public:
    // Constructor, and non virtual destructor
    Logger(const char* apChannelName, Log::Level aChannelLevel = Log::eDebug);
    ~Logger(void);

    // A Logger is copyable with its a default copy constructor and copy operator without any problem

    // Utility const method to produce Log objets, used to collect the stream to output
    Log debug(void) const;
    Log info(void) const;
    Log notice(void) const;
    Log warning(void) const;
    Log error(void) const;
    Log critic(void) const;

    inline void setLevel(Log::Level aLevel) {
       mChannelPtr->setLevel(aLevel);
    }

    inline Log::Level getLevel(void) const {
        return mChannelPtr->getLevel();
    }

    inline const std::string& getName(void) const {
        return mChannelPtr->getName();
    }


private:
    // To be used only by the Log class
    void output(const Log& aLog) const;

    static const char* toString(Log::Level aLevel);

    Channel::Ptr  mChannelPtr;
};

