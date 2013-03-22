/**
 * @file    Manager.h
 * @ingroup LoggerCpp
 * @brief   The static class that manage the registered Channel and Output objects
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Log.h"
#include "Channel.h"
#include "Output.h"
#include "Config.h"


namespace Log
{


/**
 * @brief The static class that manage the registered channels and outputs
 *
 *  The Manager keeps a map of all the named Channel objects
 * and share them on demand by new Logger objects created with the same name.
 *
 * @todo Thus the Manager is able to change the Log::Level of selected Channel object.
 *
 * The Manager also keep a list of all configured Output object to output the Log objects.
 */
struct Manager
{
public:
    static void         configure(const Config::Vector& aConfigList);
    static void         terminate(void);

    static Channel::Ptr get(const char* apChannelName);
    static void         output(const Channel::Ptr& aChannelPtr, const Log& aLog);

private:
    static Channel::Map     mChannelMap;    //!< Map of shared pointer of Channel objects
    static Output::Vector   mOutputList;    //!< List of Output objects
};


} // namespace Log
