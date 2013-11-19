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

#include "LoggerCpp/OutputFile.h"
#include "LoggerCpp/Exception.h"

#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>


namespace Log {


// Open the output file
OutputFile::OutputFile(const Config::Ptr& aConfigPtr) :
    mpFile(nullptr) {
    assert(aConfigPtr);

    mMaxStartupSize = aConfigPtr->get("max_startup_size",   (long)0);
    mMaxSize        = aConfigPtr->get("max_size",           (long)1024*1024);
    mFilename       = aConfigPtr->get("filename",           "log.txt");
    mFilenameOld    = aConfigPtr->get("filename_old",       "log.old.txt");

    // Test the size of the existing log file, rename it and open a new one if needed
    struct stat statFile;
    int ret = stat(mFilename.c_str(), &statFile);
    if (0 == ret) {
        mSize = statFile.st_size;
    }

    if (mSize > mMaxStartupSize) {
        rotate();
    } else {
        open();
    }
}

// Close the file
OutputFile::~OutputFile() {
    close();
}

// Open the file
void OutputFile::open() const {
    mpFile = fopen(mFilename.c_str(), "ab");
    if (nullptr == mpFile) {
        LOGGER_THROW("file \"" << mFilename << "\" not opened");
    }
}

// Close the file if it is opened
void OutputFile::close() const {
    if (nullptr != mpFile) {
        fclose(mpFile);
        mpFile  = nullptr;
        mSize   = 0;
    }
}

// Rotate a file : close, remove, rename, open
void OutputFile::rotate() const {
    close();

    remove(mFilenameOld.c_str());
    rename(mFilename.c_str(), mFilenameOld.c_str());

    open();
}

// Output the Log to the standard console using printf
void OutputFile::output(const Channel::Ptr& aChannelPtr, const Log& aLog) const {
    const DateTime& time = aLog.getTime();

    if (mSize > mMaxSize) {
        rotate();
    }

    if (nullptr != mpFile) {
        // uses fprintf for atomic thread-safe operation
        int nbWritten = fprintf(mpFile, "%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u  %-12s %s %s\n",
                                time.year, time.month, time.day,
                                time.hour, time.minute, time.second, time.ms,
                                aChannelPtr->getName().c_str(), Log::toString(aLog.getSeverity()),
                                (aLog.getStream()).str().c_str());
        fflush(stdout);

        mSize += nbWritten;
    }
}


} // namespace Log
