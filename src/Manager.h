/**
 * @file    Manager.h
 * @ingroup LoggerCpp
 * @brief   The static class that manage the registered channels and outputs
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

