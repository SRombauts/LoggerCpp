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

#include "Channel.h"

#include <map>
#include <string>


/**
 * @brief The static class that manage the registered channels and outputs
 *
 *  The Manager keeps a map of all the named Channel objects
 * and share them on demand by new Logger objects created with the same name.
 *
 * @todo Thus the Manager is able to change the Log::Level of selected Channel objectq.
 *
 * @todo The Manager also keep a list of all enabled Output object to output the Log objects.
 */
struct Manager
{
public:
    static Channel::Ptr get(const char* apChannelName);
    static void         output(const Channel::Ptr& aChannelPtr, const Log& aLog);

private:
    /// @brief Map of shared pointer of Channel objects
    typedef std::map<std::string, Channel::Ptr> ChannelMap;

    static ChannelMap   mChannelMap;    //!< Map of shared pointer of Channel objects
};

