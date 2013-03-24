/**
 * @file    Stream.h
 * @ingroup LoggerCpp
 * @brief   A standard string stream formatter with implicit string conversion
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <sstream>
#include <string>


namespace Log
{

/**
 * @brief   A standard string stream formatter with implicit string conversion
 *
 *  It is constructed and initialized by a call to the Stream() constructor.
 * Is is then used by successive standard stream call "<<" to insert data into the stream.
 * It is ultimatly implicitly converted to std::string when required.
 *
 *  A typical use case is to format a std::exception string message :
 * - throw std::runtime_error(Stream() << "no value for key '" << apKey << "'");
 */
class Stream
{
public:
    /// @brief Constructor
    Stream(void)    {}
    /// @brief Non virtual destructor
    ~Stream(void)   {}

    /**
     * @brief stream inserter operator
     *
     * @param[in] aValue    Value to be formatted and insterted into the string stream
     */
    template <typename T>
    Stream& operator<< (const T& aValue)
    {
        mStream << aValue;
        return (*this);
    }

    /// @brief std::string cast operator for implicit conversion
    inline operator std::string () const
    {
        return mStream.str();
    }

private:
    /// @{ Non-copyable object
    Stream(const Stream&);
    void operator=(const Stream&);
    /// @}

private:
   std::ostringstream   mStream;    //!< The underlying string stream
};


} // namespace Log

