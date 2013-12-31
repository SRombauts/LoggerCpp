# Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 2.6)
project(LoggerCpp)

# Define useful variables to handle OS/Compiler differences
if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CPPLINT_ARG_OUTPUT      "--output=vs7")
    set(CPPCHECK_ARG_TEMPLATE   "--template=vs")
    set(DEV_NULL                "NUL")
    set(SYSTEM_LIBRARIES        "")
    add_definitions (/D_CRT_SECURE_NO_WARNINGS)
else()
    set(CPPLINT_ARG_OUTPUT      "--output=eclipse")
    set(CPPCHECK_ARG_TEMPLATE   "--template=gcc")
    set(DEV_NULL                "/dev/null")
    set(SYSTEM_LIBRARIES        "rt")
#   add_definitions (-std=c++0x)  # -std=c++11
endif()
set(CPPLINT_ARG_VERBOSE "--verbose=3")

# List all sources/headers files
# used only for cpplint: adding a file still require modifing the CMakeLists.txt
# so that CMake know that it should rebuild the project (and better practice)
file(GLOB all_source_files
    "${PROJECT_SOURCE_DIR}/include/LoggerCpp/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# All includes are relative to the "include" directory
include_directories ("${PROJECT_SOURCE_DIR}/include")

# add sources of the logger library as a "LoggerCpp" library
add_library (LoggerCpp
 include/LoggerCpp/Channel.h
 include/LoggerCpp/Config.h
 include/LoggerCpp/DateTime.h
 include/LoggerCpp/Exception.h
 include/LoggerCpp/Formatter.h
 include/LoggerCpp/Log.h
 include/LoggerCpp/Logger.h
 include/LoggerCpp/LoggerCpp.h
 include/LoggerCpp/Manager.h
 include/LoggerCpp/Output.h
 include/LoggerCpp/OutputConsole.h
 include/LoggerCpp/OutputDebug.h
 include/LoggerCpp/OutputFile.h
 include/LoggerCpp/shared_ptr.hpp
 include/LoggerCpp/Utils.h
 src/Config.cpp
 src/DateTime.cpp
 src/Log.cpp
 src/Logger.cpp
 src/Manager.cpp
 src/OutputConsole.cpp
 src/OutputDebug.cpp
 src/OutputFile.cpp
)

# add the example executable, linked with the LoggerCpp library
add_executable(LoggerCpp_Example examples/Main.cpp)
target_link_libraries (LoggerCpp_Example LoggerCpp ${SYSTEM_LIBRARIES})

# add a cpplint target to the "all" target
add_custom_target(LoggerCpp_cpplint
 ALL
 COMMAND python cpplint.py ${CPPLINT_ARG_OUTPUT} ${CPPLINT_ARG_VERBOSE} ${all_source_files}
 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# add a cppcheck target to the "all" target
add_custom_target(LoggerCpp_cppcheck
 ALL
 COMMAND cppcheck -j 4 cppcheck --enable=style --quiet ${CPPCHECK_ARG_TEMPLATE} ${PROJECT_SOURCE_DIR}/src
)

if (NOT DEFINED ENV{TRAVIS})
    # add a Doxygen target to the "all" target
    add_custom_target(LoggerCpp_doxygen
     ALL
     COMMAND doxygen Doxyfile > ${DEV_NULL}
     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
else()
    # but no Doxygen under Travis CI: too costly and no real benefit
    message("no Doxygen target when TRAVIS is defined")
endif()
