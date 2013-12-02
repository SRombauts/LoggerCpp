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

#include "LoggerCpp/Output.h"
#include "LoggerCpp/Config.h"


namespace Log {


/**
 * @brief   Output to the standard console using fprintf() with stdout
 * @ingroup LoggerCpp
 */
class OutputConsole : public Output {
public:
    /// @brief Constructor : no config
    explicit OutputConsole(const Config::Ptr& aConfigPtr);

    /// @brief Destructor
    virtual ~OutputConsole();

#ifdef _WIN32
    /**
     * @brief Convert a Level to a Win32 console color text attribute
     *
     * @param[in] aLevel Log severity Level to convert
     *
     * @return Win32 console color text attribute
     */
    static unsigned short toWin32Attribute(Log::Level aLevel);
#else // _WIN32
   /**
     * @brief Convert a Level to an ANSI escape color code
     *
     * @param[in] aLevel Log severity Level to convert
     *
     * @return ANSI escape code for console color output
     */
    static unsigned int toEscapeCode(Log::Level aLevel);
#endif // _WIN32

    /**
     * @brief Output the Log to the standard console using fprintf
     *
     * @param[in] aChannelPtr   The underlying Channel of the Log
     * @param[in] aLog          The Log to output
     */
    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;
};


} // namespace Log
