/**
 * @file    Main.cpp
 * @brief   Test program for my simple logger system
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
*/
#include "../src/Logger.h"



/**
 * @brief Simple test class
 */
class Tester {
public:
    Tester() :
        mLogger("Tester")
    {
    }

    void constTest (void) const {
        mLogger.debug() << "log within a const method";
    }

private:
    Logger mLogger;
};



/**
 * @brief Simple example program
 */
int main (void)
{
    Tester tester;
    tester.constTest();

    Logger logger("TestLog");

    logger.debug()  << "Debug.";
    logger.info()   << "Info.";
    logger.notice() << "Notice.";
    logger.warning()<< "Warning.";

    logger.setLevel(Log::eWarning);

    logger.debug()  << "Debug.";
    logger.info()   << "Info.";
    logger.notice() << "Notice.";
    logger.warning()<< "Warning.";
    logger.error()  << "Error.";
    logger.critic() << "Critic.";

    logger.setLevel(Log::eDebug);
    logger.debug() << "Variable = " << std::hex << 0x75af0 << " test";
    logger.debug() << "Variable = " << std::right << std::setfill('0') << std::setw(8) << 0x75af0 << " test";

    return 0;
}
