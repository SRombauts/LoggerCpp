/**
 * @file    Main.cpp
 * @brief   Example program for the simple LoggerC++ system
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "LoggerCpp/LoggerCpp.h"

#include <iostream>


/**
 * @brief Simple test class
 */
class Tester {
public:
    Tester() :
        mLogger("main.Tester")
    {
    }

    void constTest (void) const {
        mLogger.debug() << "log within a const method";
    }

private:
    Log::Logger mLogger; ///< A named logger to produce log
};



/**
 * @brief Simple example program
 */
int main ()
{
    // Configure the default severity Level of new Channel objects
#ifndef NDEBUG
    Log::Manager::setDefaultLevel(Log::Log::eDebug);
#else
    Log::Manager::setDefaultLevel(Log::Log::eNotice);
#endif

    int val;
    if (false)
    {
        val = 2;
    }
    if (true)
    {
        // TODO SRombauts : testing
        int* p = new int(2);
    }

    // Configure the Output objects
    Log::Config::Vector configList;
    Log::Config::addOutput(configList, "OutputConsole");
    Log::Config::addOutput(configList, "OutputFile");
    Log::Config::setOption(configList, "filename",          "log.txt");
    Log::Config::setOption(configList, "filename_old",      "log.old.txt");
    Log::Config::setOption(configList, "max_startup_size",  "0");
    Log::Config::setOption(configList, "max_size",          "10000");
#ifdef WIN32
    Log::Config::addOutput(configList, "OutputDebug");
#endif

    // Create a Logger object, using a "Main.Example" Channel
    Log::Logger logger("Main.Example");
    logger.warning() << "NO logs before configure()";

    try
    {
        // Configure the Log Manager (create the Output objects)
        Log::Manager::configure(configList);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }
    
    // Test outputs of various kind of variables, and some common stream manipulations.
    std::string     str("string");
    unsigned int    ui  = 123;
    double          dbl = -0.023f;
    logger.debug() << "Variables ; '" << str << "', '" << ui << "', '" << dbl << "'";
    logger.debug() << "Hexa = " << std::hex << 0x75af0 << " test";
    logger.debug() << "Deci = " << std::right << std::setfill('0') << std::setw(8) << 76035 << " test";
    logger.debug() << "sizeof(logger)=" << sizeof(logger);

    // Test outputs of various severity Level
    logger.debug()  << "Debug.";
    logger.info()   << "Info.";
    logger.notice() << "Notice.";
    logger.warning()<< "Warning.";
    logger.error()  << "Error.";
    logger.critic() << "Critic.";

    // Modify the output Level of the underlying Channel, and test various severity Level again
    logger.setLevel(Log::Log::eWarning);
    logger.debug()  << "NO Debug.";     // NO more debug logs
    logger.info()   << "NO Info.";      // NO more info logs
    logger.notice() << "NO Notice.";    // NO more notice logs
    logger.warning()<< "Warning.";
    logger.error()  << "Error.";
    logger.critic() << "Critic.";
    
    // Reset Level of the "Main.example" channel by its name
    Log::Manager::get("Main.Example")->setLevel(Log::Log::eDebug);
    
    // Create other loggers, sharing the "Main.Example" Channel, and creating a new one
    Log::Logger logger2("Main.Example");
    Log::Logger logger3("Main.Other");
    logger.debug() << "First logger to the Channel";
    logger2.debug() << "Second logger to the Channel";
    logger3.debug() << "Third logger, other Channel";
    // Modify the Level of the "Main.example" channel by its name
    Log::Manager::get("Main.Example")->setLevel(Log::Log::eInfo);
    logger.debug() << "first logger inhibited";         // NO more debug logs for this logger
    logger2.debug() << "second logger also disabled";   // NO more debug logs (sharing the same underlying channel)
    logger3.debug() << "third logger still active";
    // Reset the Level of the "Main.example" channel by its name
    Log::Manager::get("Main.Example")->setLevel(Log::Log::eDebug);
    logger.debug() << "first logger re-activated";
    logger2.debug() << "second logger also re-activated";
    logger3.debug() << "third logger always active";

    // Create an object using a Logger as member variable
    Tester tester;
    tester.constTest();

    // Show how to get the current Channel configuration (to save it to a file, for instance)
    Log::Manager::get("Main.OtherChannel")->setLevel(Log::Log::eNotice);
    Log::Config::Ptr ChannelConfigPtr = Log::Manager::getChannelConfig();
    // Show how to set the current Channel configuration (restored from a file, for instance)
    Log::Manager::setChannelConfig(ChannelConfigPtr);

    // Terminate the Log Manager (destroy the Output objects)
    Log::Manager::terminate();
    logger.warning() << "NO more logs after terminate()";

    return 0;
}
