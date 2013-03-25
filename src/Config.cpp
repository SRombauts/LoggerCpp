/**
 * @file    Config.cpp
 * @ingroup LoggerCpp
 * @brief   Configuration for an Output object
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Config.h"
#include "Exception.h"


namespace Log
{


// Constructor
Config::Config(const char* apName) :
    mName(apName)
{
}

// Destructor
Config::~Config(void)
{
}

// Get a string value
const std::string& Config::getString(const char* apKey) const
{
    Config::Values::const_iterator iValue = mValues.find(apKey);
    if (mValues.end() == iValue) {
        LOGGER_THROW("no value for the \"" << apKey << "\" key");
    }
    return iValue->second;
}


} // namespace Log
