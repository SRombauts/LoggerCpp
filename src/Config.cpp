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

#include "LoggerCpp/Config.h"
#include "LoggerCpp/Exception.h"

#include <cstdlib>


namespace Log {


// Constructor
Config::Config(const char* apName) :
    mName(apName) {
}

// Destructor
Config::~Config(void) {
}

// Get a string value
const char* Config::get(const char* apKey, const char* apDefaultValue) const {
    const char* pValue;
    Config::Values::const_iterator iValue = mValues.find(apKey);
    if (mValues.end() != iValue) {
        pValue = iValue->second.c_str();
    } else  {
        pValue = apDefaultValue;
    }
    return pValue;
}

// Get a string value
long Config::get(const char* apKey, long aDefaultValue) const {
    long value;
    Config::Values::const_iterator iValue = mValues.find(apKey);
    if (mValues.end() != iValue) {
        value = atol(iValue->second.c_str());
    } else  {
        value = aDefaultValue;
    }
    return value;
}

// Create the Config for a new Output
void Config::addOutput(Vector& aConfigList, const char* apOutputName) {
    Log::Config::Ptr configPtr(new Log::Config(apOutputName));
    aConfigList.push_back(configPtr);
}

// Set an option for the last added Output
void Config::setOption(Vector& aConfigList, const char* apKey, const char* apValue) {
    (*aConfigList.back()).setValue(apKey, apValue);
}

} // namespace Log
