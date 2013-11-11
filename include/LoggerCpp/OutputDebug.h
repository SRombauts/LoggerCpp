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

#include "LoggerCpp/Output.h"
#include "LoggerCpp/Config.h"


namespace Log {


/**
 * @brief   Output to the Visual Studio debugger using OutputDebugString()
 * @ingroup LoggerCpp
 */
class OutputDebug : public Output {
public:
    /// @brief Constructor : no config
    explicit OutputDebug(const Config::Ptr& aConfigPtr);

    /// @brief Destructor
    virtual ~OutputDebug();

    /**
     * @brief Output the Log to the Visual Studio debugger using OutputDebugString()
     *
     * @param[in] aChannelPtr   The underlying Channel of the Log
     * @param[in] aLog          The Log to output
     */
    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;
};


} // namespace Log
