/**
 * @file    Time.h
 * @ingroup LoggerCpp
 * @brief   Current time precise to the millisecond.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once


namespace Log
{


/**
 * @brief   Current time precise to the millisecond.
 * @ingroup LoggerCpp
 */
struct Time
{
    Time(void);

    int ms;      /* milliseconds */
    int sec;     /* seconds [0,59] */
    int min;     /* minutes [0,59] */
    int hour;    /* hours   [0,23] */
    int day;     /* day     [1,31] */
    int month;   /* month   [1,12] */
    int year;    /* year    [0,30827]*/
};


} // namespace Log
