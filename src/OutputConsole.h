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
    /// @brief Constructor : no config
    OutputConsole(const Config::Ptr& aConfigPtr);

    /// @brief Destructor
    virtual ~OutputConsole();

    /**
     * @brief Output the Log to the standard console using fprintf
     *
     * @param[in] aChannelPtr   The underlying Channel of the Log
     * @param[in] aLog          The Log to output
     */
    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;
};


} // namespace Log
