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
#include <sys/types.h>
#include <sys/stat.h>


namespace Log
{


// Open the output file
OutputFile::OutputFile(const Config::Ptr& aConfigPtr) :
    mpFile(NULL)
{
    assert(aConfigPtr);

    mMaxStartupSize = aConfigPtr->get("max_startup_size",   (long)0);
    mMaxSize        = aConfigPtr->get("max_size",           (long)1024*1024);
    mFilename       = aConfigPtr->get("filename",           "log.txt");
    mFilenameOld    = aConfigPtr->get("filename_old",       "log.old.txt");

    // Test the size of the existing log file, rename it and open a new one if needed
    test_rotate(mMaxStartupSize);
    if (NULL == mpFile)
    {
        open();
    }
}

// Close the file
OutputFile::~OutputFile()
{
    close();
}

// Open the file
void OutputFile::open() const
{
    mpFile = fopen(mFilename.c_str(), "ab");
    if (NULL == mpFile)
    {
        LOGGER_THROW("file \"" << mFilename << "\" not opened");
    }
}

// Close the file if it is opened
void OutputFile::close() const
{
    if (NULL != mpFile)
    {
        fclose(mpFile);
        mpFile = NULL;
    }
}

/// @todo Rotate a file : remove(), rename()
void OutputFile::test_rotate(const long aSize) const
{
    struct stat statFile;
    memset((void*)&statFile, 0, sizeof(statFile)); 
    stat(mFilename.c_str(), &statFile);
    if (statFile.st_size > aSize)
    {
        close();
        
        remove(mFilenameOld.c_str());
        rename(mFilename.c_str(), mFilenameOld.c_str());

        open();
    }
}

// Output the Log to the standard console using printf
void OutputFile::output(const Channel::Ptr& aChannelPtr, const Log& aLog) const
{
    const Time& time = aLog.getTime();

    test_rotate(mMaxSize);

    if (NULL != mpFile)
    {
        // uses fprintf for atomic thread-safe operation
        fprintf(mpFile, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u  %-20s %s  %s\n",
                time.year, time.month, time.day,
                time.hour, time.minute, time.second, time.ms,
                aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()), (aLog.getStream()).str().c_str());
        fflush(stdout);
    }
}


} // namespace Log
