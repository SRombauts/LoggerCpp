/**
 * @file    OutputFile.h
 * @ingroup LoggerCpp
 * @brief   Output to the a file using fprintf
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
 * @brief   Output to the standard console using fprintf
 * @ingroup LoggerCpp
 */
class OutputFile : public Output
{
public:
    /**
     * @brief Constructor : open the output file
     *
     * @param[in] aConfigPtr    Config the output file with "filename"
     */
    OutputFile(const Config::Ptr& aConfigPtr);

    /// @brief Destructor : close the file
    virtual ~OutputFile();

    /**
     * @brief Output the Log to the standard console using fprintf
     *
     * @param[in] aChannelPtr   The underlying Channel of the Log
     * @param[in] aLog          The Log to output
     */
    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;

private:
    FILE* mpFile;   //!< File pointer
};


} // namespace Log
