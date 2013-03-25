/**
 * @file    OutputFile.cpp
 * @ingroup LoggerCpp
 * @brief   Output to the standard console using printf
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "OutputFile.h"
#include "Exception.h"

#include <cstdio>


namespace Log
{

OutputFile::OutputFile(const Config::Ptr& aConfigPtr) :
    mpFile(NULL)
{
    assert(aConfigPtr);

    /// @todo Add other parameters : max_size, numer_of_file, append vs create...
    const std::string& filename = aConfigPtr->getString("filename");
    mpFile = fopen(filename.c_str(), "ab");
    if (NULL == mpFile)
    {
        LOGGER_THROW("file \"" << filename << "\" not opened");
    }
}

OutputFile::~OutputFile()
{
    if (NULL != mpFile)
    {
        fclose(mpFile);
        mpFile = NULL;
    }
}


/**
 * @brief Output the Log to the standard console using printf
 *
 * @param[in] aChannelPtr   The underlying Channel of the Log
 * @param[in] aLog          The Log to output
 */
void OutputFile::output(const Channel::Ptr& aChannelPtr, const Log& aLog) const
{
    const Time& time = aLog.getTime();

    // uses fprintf for atomic thread-safe operation
    fprintf(mpFile, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u  %-20s %s  %s\n",
            time.year, time.month, time.day,
            time.hour, time.minute, time.second, time.ms,
            aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()), (aLog.getStream()).str().c_str());
    fflush(stdout);
}


} // namespace Log
