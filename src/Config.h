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

// The following includes "boost/shared_ptr.hpp" if LOGGER_USE_BOOST_SHARED_PTR is defined,
// or <memory> (or <tr1/memory>) when C++11 (or experimental C++0x) is available,
// or a custom minimal shared_ptr implementation,
// and imports the "shared_ptr" symbol inside the Log namespace (ie. Log::shared_ptr)
#include "shared_ptr.hpp"


namespace Log
{


// forward declaration
class Logger;


/**
 * @brief   Configuration for an Output object
 * @ingroup LoggerCpp
 *
 *  A Config object is an associative container of strings key and values,
 * with easy to use helper manipulation functions.
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
     * @brief Get a string value, or return the provided default one
     *
     * @param[in] apKey             String key identifying the string value
     * @param[in] apDefaultValue    String default value 
     *
     * @return String value associated to the given key
     */
    const char* get(const char* apKey, const char* apDefaultValue) const;

    /**
     * @brief Get a long value, or return the provided default one
     *
     * @param[in] apKey         String key identifying the string value
     * @param[in] aDefaultValue Long default value 
     *
     * @return Long value associated to the given key
     */
    long get(const char* apKey, const long aDefaultValue) const;

public:
    /**
     * @brief Create the Config for a new Output
     *
     * @param[in,out]   aConfigList     Config list to complete with a new Output
     * @param[in]       apOutputName    Name of the new Output
     */

    static void addOutput(Vector& aConfigList, const char* apOutputName);
    /**
     * @brief Set an option for the last added Output
     *
     * @param[in,out]   aConfigList Config list to complete with a new option value
     * @param[in]       apKey       String key identifying the string value
     * @param[in]       apValue     String value associated to the given key
     */
    static void setOption(Vector& aConfigList, const char* apKey, const char* apValue);

private:
   std::string  mName;      //!< Name of the Config
   Values       mValues;    //!< Map of string values
};


} // namespace Log

