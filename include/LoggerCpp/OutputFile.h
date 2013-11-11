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

#include "LoggerCpp/Output.h"
#include "LoggerCpp/Config.h"

#include <string>


namespace Log {


/**
 * @brief   Output to the standard console using fprintf
 * @ingroup LoggerCpp
 */
class OutputFile : public Output {
public:
    /**
     * @brief Constructor : open the output file
     *
     * @param[in] aConfigPtr    Config the output file with "filename"
     */
    explicit OutputFile(const Config::Ptr& aConfigPtr);

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
    /// @brief Open the log file
    void open() const;
    /// @brief Close the log file
    void close() const;
    /// @brief Rotate the log file : close, remove, rename, open
    void rotate() const;

private:
    mutable FILE*   mpFile; ///< @brief File pointer (mutable to be modified in the const output method)
    mutable long    mSize;  ///< @brief Current size of the log file (mutable to be modified in the const output method)

    /** 
     * @brief "max_startup_size" : Size of the file above which to create a new file instead of appending to it (at startup).
     *
     * Default (0) creates a new file at each startup (never append to an existing one).
    */
    long        mMaxStartupSize;

    /** 
     * @brief "max_size" : Size of the file above which to create a new file instead of appending to it (at runtime).
     *
     * Default (1024*1024=1Mo) creates a new file each time the current one grow above 1Mo.
    */
    long        mMaxSize;

    /**
     * @brief "filename" : Name of the log file
     */
    std::string mFilename;

    /**
     * @brief "filename_old" : Name of the log file renamed after max_size is reach
     */
    std::string mFilenameOld;
};


} // namespace Log
