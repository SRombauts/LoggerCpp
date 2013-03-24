/**
 * @file    OutputConsole.h
 * @ingroup LoggerCpp
 * @brief   Output to the standard console using fprintf() with stdout
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
 * @brief   Output to the standard console using fprintf() with stdout
 * @ingroup LoggerCpp
 */
class OutputConsole : public Output
{
public:
    OutputConsole(const Config::Ptr& aConfigPtr);
    virtual ~OutputConsole();

    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;
};


} // namespace Log
