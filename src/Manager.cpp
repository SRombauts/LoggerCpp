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
#ifdef WIN32
#include "OutputDebug.h"
#endif

#include <stdexcept>


namespace Log
{


Channel::Map    Manager::mChannelMap;
Output::Vector  Manager::mOutputList;


/**
 * @brief Create and configure the Output objects
 *
 * @param[in] aConfigList   List of Config for Output objects
*/
void Manager::configure(const Config::Vector& aConfigList)
{
    // List of all Output class ; those names are in the form 
    // - "class Log::OutputConsole" under Visual Studio 2010
    // - "N3Log13OutputConsoleE" under GCC
    std::string outputConsole = typeid(OutputConsole).name();
    std::string outputFile    = typeid(OutputFile).name();
#ifdef WIN32
    std::string outputDebug   = typeid(OutputDebug).name();
#endif

    Config::Vector::const_iterator  iConfig;
    for (iConfig  = aConfigList.begin();
         iConfig != aConfigList.end();
         ++iConfig)
    {
        Output::Ptr         outputPtr;
        const std::string&  configName = (*iConfig)->getName();

        // Compare the provided Output name with the known class name
        if (std::string::npos != outputConsole.find(configName))
        {
            outputPtr.reset(new OutputConsole((*iConfig)));
        }
        else if (std::string::npos != outputFile.find(configName))
        {
            outputPtr.reset(new OutputFile((*iConfig)));
        }
#ifdef WIN32
        else if (std::string::npos != outputDebug.find(configName))
        {
            outputPtr.reset(new OutputDebug((*iConfig)));
        }
#endif
        else
        {
            throw std::runtime_error("Unknown Output name");
        }
        mOutputList.push_back(outputPtr);
    }
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
 *
 * @return Pointer to the corresponding Channel (never NULL)
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

