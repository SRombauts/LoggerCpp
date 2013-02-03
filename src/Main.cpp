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


class Tester {
public:
    Tester() :
        mLogger("Tester")
    {
    }

    void constTest (void) const {
        mLogger.debug().test("test") << ", toto.";
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
    logger.notice().test("Info.");
    logger.info().test("Notice.");
    logger.notice().test("Notice.");
    logger.warning().test("Warning.");

    logger.setLevel(Log::eWarning);

    logger.debug().test("Three, ").test("four.");
    logger.info().test("Three, ").test("four.");
    logger.notice().test("Three, ").test("four.");
    logger.warning().test("Three, ").test("four.");
    logger.error().test("Three, ").test("four.");
    logger.critic().test("Crash.");

    logger.setLevel(Log::eDebug);
    logger.debug().test("Five, ").test("six.");

    return 0;
}
