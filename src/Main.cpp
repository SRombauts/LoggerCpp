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
 * @brief Simple example program
 */
int main (void)
{
   Logger logger("TestLog");

   logger.debug().test("One, ").test("two.");
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
   logger.crash().test("Three, ").test("four.");

   logger.setLevel(Log::eDebug);
   logger.debug().test("Five, ").test("six.");

   return 0;
}
