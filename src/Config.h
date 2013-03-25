/**
 * @file    Config.h
 * @ingroup LoggerCpp
 * @brief   Configuration for an Output object
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <string>
#include <vector>
#include <map>

/// @todo try first for the C++11 std::shared_ptr, or the minimal shared_ptr implementation
#include <boost/shared_ptr.hpp>
#define shared_ptr  boost::shared_ptr


namespace Log
{


// forward declaration
class Logger;


/**
 * @brief   Configuration for an Output object
 * @ingroup LoggerCpp
 */
class Config
{
public:
    /// @brief Shared Pointer to a Config object
    typedef shared_ptr<Config>                  Ptr;
    /// @brief List of Config objects
    typedef std::vector<Ptr>                    Vector;
    /// @brief Map of string values
    typedef std::map<std::string, std::string>  Values;

public:
    /**
     * @brief Constructor
     *
     * @param[in] apName Name of the Config object
     */
    Config(const char* apName);

    /// @brief Non virtual destructor
    ~Config(void);

    /// @brief Get the name of this Config object
    inline const std::string& getName(void) const {
        return mName;
    }

    /// @brief Get the string values of this Config object
    inline const Values& getValues(void) const {
        return mValues;
    }

    /**
     * @brief Set a string value
     *
     * @param[in] apKey     String key identifying the string value
     * @param[in] apValue   String value associated to the given key
     */
    inline void setValue(const char* apKey, const char* apValue) {
        mValues[apKey] = apValue;
    }

    /**
     * @brief Get a string value
     *
     *  Throw a std::runtime_error if the key does not exists.
     *
     * @param[in] apKey String key identifying the string value
     *
     * @return String value associated to the given key
     */
    const std::string& getString(const char* apKey) const;

private:
   std::string  mName;      //!< Name of the Config
   Values       mValues;    //!< Map of string values
};


} // namespace Log

