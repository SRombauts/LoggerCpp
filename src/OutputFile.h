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
 * @brief Output to the standard console using printf
 */
class OutputFile : public Output
{
public:
    OutputFile(const Config::Ptr& aConfigPtr);
    virtual ~OutputFile();

    virtual void output(const Channel::Ptr& aChannelPtr, const Log& aLog) const;

private:
    FILE* mpFile;
};


} // namespace Log
