/**
 * @file    OutputSyslog.h
 * @ingroup LoggerCpp
 * @brief   Output to Unix syslog
 * @author  andre
 *
 * Copyright (c) 2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#ifdef __unix__

#include <LoggerCpp/Output.h>
#include <LoggerCpp/Config.h>

#include <string>


namespace Log {


/**
 * @brief   Output to the unix system syslog. Buffering & flushing is done by syslog itself.
 * @ingroup LoggerCpp
 */
class OutputSyslog : public Output {
public:
    /**
     * @brief Open the syslog file
     *
     * @param[in] aConfigPtr    Config the output file with "filename"
     */
    explicit OutputSyslog(const Config::Ptr& aConfigPtr);

    /// @brief Destructor : close the syslog file
    virtual ~OutputSyslog();

    /**
     * @brief Output the Log to the syslog
     *
     * @param[in] aChannelPtr   The underlying Channel of the Log
     * @param[in] aLog          The Log to output
     */
    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;

private:
    /**
     * @brief "name" : Name (prefix) of the entry in syslog.
     */
    std::string mLogname;
};


} // namespace Log

#endif // __unix__
