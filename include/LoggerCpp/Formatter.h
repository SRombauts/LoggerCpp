/**
 * @file    Formatter.h
 * @ingroup LoggerCpp
 * @brief   A standard string stream formatter with implicit string conversion
 *
 * Copyright (c) 2013-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <sstream>
#include <string>


namespace Log {

/**
 * @brief   A standard string stream formatter with implicit string conversion
 * @ingroup LoggerCpp
 *
 *  It is constructed and initialized by a call to the Formatter() constructor.
 * Is is then used by successive standard stream call "<<" to insert data into the stream.
 * It is ultimately implicitly converted to std::string when required.
 *
 *  A typical use case is to format a std::exception string message :
 * - throw std::runtime_error(Formatter() << "no value for key '" << apKey << "'");
 */
class Formatter {
public:
    /// @brief Constructor
    Formatter(void)    {}
    /// @brief Non virtual destructor
    ~Formatter(void)   {}

    /**
     * @brief stream inserter operator
     *
     * @param[in] aValue    Value to be formatted and inserted into the string stream
     *
     * @return Current Formatter instance
     */
    template <typename T>
    Formatter& operator<< (const T& aValue) {
        mStream << aValue;
        return (*this);
    }

    /// @brief std::string cast operator for implicit conversion
    inline operator std::string() const {
        return mStream.str();
    }

private:
    /// @{ Non-copyable object
    Formatter(const Formatter&);
    void operator=(const Formatter&);
    /// @}

private:
    std::ostringstream   mStream;    ///< The underlying string stream
};


} // namespace Log

