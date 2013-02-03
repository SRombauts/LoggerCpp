/**
 * (c) INEO Systrans 2013
 *
 * @file    Main.cpp
 *
 * @brief   Test program for my simple logger system
 *
 * @author  02/02/2013 SRombauts
*/
#include "Logger.h"



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

    logger.debug() << "One, " << "two.";
    logger.notice() << "Info.";
    logger.info() << "Notice.";
    logger.notice() << "Notice.";
    logger.warning() << "Warning.";

    logger.setLevel(Log::eWarning);

    logger.debug() << "Three" << "four.";
    logger.info() << "Three, " << "four.";
    logger.notice() << "Three, " << "four.";
    logger.warning() << "Three, " << "four.";
    logger.error() << "Three, " << "four.";
    logger.critic() << "Crash.";

    logger.setLevel(Log::eDebug);
    logger.debug() << "Five, " << "six.";

    return 0;
}
