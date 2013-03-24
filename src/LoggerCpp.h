/**
 * @file    LoggerCpp.h
 * @ingroup LoggerCpp
 * @brief   LoggerC++ (LoggerCpp) is a simple, elegant and efficient C++ logger library.
 *
 * Include this main header file in your project to gain access to all functionality provided by the logger.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
/**
 * @defgroup LoggerCpp LoggerC++
 * @brief    LoggerC++ (LoggerCpp) is a simple, elegant and efficient C++ logger library.
 */
#pragma once


// Include useful headers of LoggerC++
#include "Logger.h"
#include "Manager.h"


/**
 * @brief   Version numbers for LoggerC++
 * @ingroup LoggerCpp
 *
 * The [LOGGERCPP_VERSION] C preprocessor macro in the LoggerCpp.h header
 * evaluates to a string literal that is the LoggerC++ version in the
 * format "X.Y.Z" where X is the major version number
 * and Y is the minor version number and Z is the release number.
 *
 * The [LOGGERCPP_VERSION_NUMBER] C preprocessor macro resolves to an integer
 * with the value (X*1000000 + Y*1000 + Z) where X, Y, and Z are the same
 * numbers used in [LOGGERCPP_VERSION].
 */
#define LOGGERCPP_VERSION             "0.0.0"
#define LOGGERCPP_VERSION_NUMBER      0000000
