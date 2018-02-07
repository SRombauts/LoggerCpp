/**
 * @file    Exception.h
 * @ingroup LoggerCpp
 * @brief   Encapsulation of an error message on a std::runtime_error.
 *
 * Copyright (c) 2012-2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <LoggerCpp/Formatter.h>

#include <stdexcept>
#include <cassert>
#include <string>


/// assert() is used in destructors, where exceptions are not allowed
/// (only asserting in debug mode)
/// @todo Enable assertion callback like in SQLiteC++
#define LOGGER_ASSERT(expression) assert(expression)



#ifdef _WIN32
// Disable warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#pragma warning(disable:4290)
#endif


namespace Log {

/**
 * @brief   Encapsulation of an error message based on std::runtime_error.
 * @ingroup LoggerCpp
 */
class Exception : public std::runtime_error {
public:
    /**
     * @brief Encapsulation of an error message based on std::runtime_error.
     *
     * @param[in] aErrorMessage The string message describing the error
     */
    explicit Exception(const std::string& aErrorMessage) :
        std::runtime_error(aErrorMessage)
    {}
};


/// @brief Stringify 1/2 : convert an integer to a string (using the following macro)
#define TOSTRING(x) _XSTRING(x)
/// @brief Stringify 2/2 : convert an integer to a string (inner macro)
#define _XSTRING(x) #x

#ifdef __FUNCTION__
/// @brief Define __func__ under Windows, to use the same name as with GCC
#define __func__    __FUNCTION__
#endif

/// @brief Helper macro to throw an Exception with file/line/function information, using the string stream Formatter
#define LOGGER_THROW(x) throw Exception(Formatter() << __FILE__ << ":" << TOSTRING(__LINE__) << ": " << __func__ << "(): " << x)


}  // namespace Log
