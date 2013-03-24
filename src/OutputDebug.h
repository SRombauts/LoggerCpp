/**
 * @file    OutputDebug.h
 * @ingroup LoggerCpp
 * @brief   Output to the Visual Studio debugger using OutputDebugString()
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Output.h"
#include "Config.h"


namespace Log
{


/**
 * @brief   Output to the Visual Studio debugger using OutputDebugString()
 * @ingroup LoggerCpp
 */
class OutputDebug : public Output
{
public:
    OutputDebug(const Config::Ptr& aConfigPtr);
    virtual ~OutputDebug();

    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;
};


} // namespace Log
