cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

###############
# Prepare Unittest library CATCH
# https://github.com/catchorg/Catch2/blob/master/single_include/catch2/catch.hpp
###############

# git clone the repository
include(ExternalProject)
ExternalProject_Add(
    catch2_project
    PREFIX ${CMAKE_BINARY_DIR}/catch2
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../external/Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG origin/master
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
# CONFIGURE BUILD and INSTALL are passed an empty string to prevent those unrequired steps.

# save location git repository in SOURCE_DIR
ExternalProject_Get_Property(catch2_project SOURCE_DIR)

# path to directory containing catch2 header
set(CATCH2_INCLUDE_DIR ${SOURCE_DIR}/single_include/catch2)

###############
# Unittests - filesystem
###############

# Name of the test project
set(TEST_PROJECT_NAME UnitTest_FileSystem)
project(${TEST_PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX)

# Find out if the current architecture is 32 or 64 bit and
# This will add the equal of '#define BUILD_ARCH_64BIT' to each file in case of a 64bit architecture
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_definitions(-DBUILD_ARCH_64BIT)
endif ()

# Gather src files that depending on a specific OS
set(SRC_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../src)
if (UNIX)
    if (APPLE AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(PLATFORM_DEPENENT_FILES ${SRC_LOCATION}/filesystem_LINUX.cpp test_filesystem_DARWIN.cpp)
    else ()
        set(PLATFORM_DEPENENT_FILES ${SRC_LOCATION}/filesystem_LINUX.cpp test_filesystem_LINUX.cpp)
#        set(PLATFORM_DEPENENT_FILES ${SRC_LOCATION}/filesystem_LINUX.cpp test_filesystem_WIN32.cpp)
    endif ()
elseif (WIN32)
    set(PLATFORM_DEPENENT_FILES ${SRC_LOCATION}/filesystem_WIN32.cpp test_filesystem_WIN32.cpp)
else ()
    message(SEND_ERROR "Unknown OS")
endif ()

# Project will be made into an executable
set(INCLUDE_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_executable(${TEST_PROJECT_NAME}
    ${PLATFORM_DEPENENT_FILES}
    ${INCLUDE_LOCATION}/filesystem.h
    )

# This will specify, for this project only, /src and /include as the folders to look into for files
target_include_directories(${TEST_PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_LOCATION}>
    $<INSTALL_INTERFACE:include>
    ${INCLUDE_LOCATION}
    PRIVATE
    ${SRC_LOCATION}
    ${CATCH2_INCLUDE_DIR}
    )
# Note, that the catch2 library lcation was added

# Make sure that Catch2 exists
add_dependencies(${TEST_PROJECT_NAME} catch2_project)

# Adding test for 'ctest'
add_test(
    NAME ${TEST_PROJECT_NAME}
    COMMAND ${TEST_PROJECT_NAME})

