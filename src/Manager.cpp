/**
 * @file    Manager.cpp
 * @ingroup LoggerCpp
 * @brief   The static class that manage the registered channels and outputs
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Manager.h"

#include "OutputConsole.h"
#include "OutputFile.h"


namespace Log
{


Channel::Map    Manager::mChannelMap;
Output::Vector  Manager::mOutputList;


/**
 * @brief Create and configure the Output objects
*/
void Manager::configure(void)
{
    //const char* pTypeName = typeid(OutputConsole).name();
    Config::Ptr configPtr;
    Output::Ptr outputPtr(new OutputConsole(configPtr));
    mOutputList.push_back(outputPtr);

    configPtr.reset (new Config(""));
    configPtr->setValue("filename", "log.txt");
    outputPtr.reset(new OutputFile(configPtr));
    mOutputList.push_back(outputPtr);
}


/**
 * @brief Destroy the Output objects
*/
void Manager::terminate(void)
{
    // This effectively destroys the Output
    mOutputList.clear();
}


/**
 * @brief Return the Channel corresponding to the provided name
 *
 * Create a new Channel or get the existing one. 
 *
 * @param[in] apChannelName String to identify the underlying Channel of a Logger
*/
Channel::Ptr Manager::get(const char* apChannelName)
{
    Channel::Ptr            ChannelPtr;
    Channel::Map::iterator  iChannelPtr = mChannelMap.find(apChannelName);

    if (mChannelMap.end() != iChannelPtr) {
        ChannelPtr = iChannelPtr->second;
    } else {
        ChannelPtr.reset(new Channel(apChannelName));
        mChannelMap[apChannelName] = ChannelPtr;
    }

    return ChannelPtr;
}


/**
 * @brief Output the Log to all the active Output objects.
 *
 * Dispatch the Log to OutputConsole/OutputFile/OutputVS/OutputMemory...
 *
 * @param[in] aChannelPtr   The underlying Channel of the Log
 * @param[in] aLog          The Log to output
 */
void Manager::output(const Channel::Ptr& aChannelPtr, const Log& aLog)
{
    Output::Vector::iterator    iOutputPtr;

    /// @todo get the current time once for all Output objects
    for (iOutputPtr  = mOutputList.begin();
         iOutputPtr != mOutputList.end();
         iOutputPtr++)
    {
        (*iOutputPtr)->output(aChannelPtr, aLog);
    }
}


} // namespace Log

