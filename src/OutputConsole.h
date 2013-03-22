/**
 * @file    OutputConsole.h
 * @ingroup LoggerCpp
 * @brief   Output to the standard console using printf
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include "Output.h"


namespace Log
{


/**
 * @brief Output to the standard console using printf
 */
class OutputConsole : public Output
{
public:
    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;
};


} // namespace Log
