cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

###############
# Prepare Unittest library CATCH
# https://github.com/catchorg/Catch2/blob/master/single_include/catch2/catch.hpp
###############

# needed in case it is loaded from another project
if (NOT TARGET catch2_project)
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
endif ()
