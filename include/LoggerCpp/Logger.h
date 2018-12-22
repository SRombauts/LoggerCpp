/**
 * @file    Logger.h
 * @ingroup LoggerCpp
 * @brief   A simple thread-safe Logger class
 *
 * Copyright (c) 2013-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <LoggerCpp/Log.h>
#include <LoggerCpp/Channel.h>

#include <string>


/**
 * @brief   LoggerC++ (LoggerCpp) is a simple, elegant and efficient C++ logger library.
 * @ingroup LoggerCpp
*/
namespace Log {


/**
 * @brief   A simple thread-safe logger class
 * @ingroup LoggerCpp
 *
 *  Logger is designed to be easy to use, light (size of a shared_ptr) and efficient.
 * It can be used as a member variable, and will not consume much CPU
 * if the log severity is below the Logger current Log::Level.
 *
 * @note A Logger object is copyable without any limitations
 */
class Logger {
    friend class Log;

public:
    /**
     * @brief Initialize a Logger utility object
     *
     * @param[in] apChannelName    String to identify origin of Log output by this Logger
     */
    explicit Logger(const char* apChannelName);
    /**
     * @brief Non virtual destructor
     */
    ~Logger(void);

    // A Logger is copyable with its a default copy constructor and copy operator without any problem

    /// @{ Utility const method to produce Log objets, used to collect the stream to output
    Log debug(void) const;
    Log info(void) const;
    Log notice(void) const;
    Log warning(void) const;
    Log error(void) const;
    Log critic(void) const;
    /// @}

    /// @brief Name of the underlying Channel
    inline const std::string& getName(void) const {
        return mChannelPtr->getName();
    }

    /// @brief Set the current output Log::Level of the underlying Channel
    inline void setLevel(Log::Level aLevel) {
        mChannelPtr->setLevel(aLevel);
    }

    /// @brief Current Log::Level of the underlying Channel
    inline Log::Level getLevel(void) const {
        return mChannelPtr->getLevel();
    }

private:
    /**
     * @brief Output the Log. Used only by the Log class destructor.
     *
     * @param[in] aLog  The Log to output
     */
    void output(const Log& aLog) const;

private:
    Channel::Ptr  mChannelPtr;   ///< Shared pointer to the underlying Channel
};


} // namespace Log

