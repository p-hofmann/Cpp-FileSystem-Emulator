/**
 * Created by Peter Hofmann on 07.01.19.
 */

#define CATCH_CONFIG_MAIN  // Tells Catch to provide a main()
#define CHECK_MESSAGE(cond, msg) do { INFO(msg); CHECK(cond); } while((void)0, 0)
#define REQUIRE_MESSAGE(cond, msg) do { INFO(msg); REQUIRE(cond); } while((void)0, 0)

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "catch.hpp"
#include "filesystem.h"

using namespace std;

/*!
 * Testing filename()
 */

TEST_CASE("Test filename", "[FileSystem]")
{
    const map<string, string> testCases = {
            {"C:\\foo\\bar.txt", "bar.txt"},
            {"C:\\foo\\.bar",    ".bar"},
            {"C:\\foo\\bar\\",   "bar"},
            {"C:\\foo\\.",       "."},
            {"C:\\foo\\..",      ".."},
            {".",                "."},
            {"..",               ".."},
            {"C:\\",             ""},
            {"C:\\host",         "host"},
            {"C:\\\\host",       "host"},
            {"C:\\\\\\host",     "host"}
    };

    string output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).filename();
        CHECK_MESSAGE(output == it->second,
                      "basename '" << it->first << "' -> '" << it->second << "' : '" << output << "'");
    }
}

/*!
 * Testing parent_path()
 */
TEST_CASE("Test parent_path", "[FileSystem]")
{
    const map<string, string> testCases = {
            {"C:\\foo\\bar.txt", "C:\\foo"},
            {"C:\\foo\\.bar",    "C:\\foo"},
            {"C:\\foo\\bar\\",   "C:\\foo"},
            {"C:\\foo\\.",       "C:\\foo"},
            {"C:\\foo\\..",      "C:\\foo"},
            {".",                ""},
            {"..",               ""},
            {"C:\\",             "C:\\"},
            {"C:\\host",         "C:\\"},
            {"C:\\\\host",       "C:\\"},
            {"C:\\\\\\host",     "C:\\"}
    };

    string output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).parent_path();
        CHECK(output == it->second);
        CHECK_MESSAGE(output == it->second,
                      "dirname '" << it->first << "' -> '" << it->second << "' : '" << output << "'");
    }
}

/*!
 * Testing is_absolute()
 */
TEST_CASE("Test is_absolute", "[FileSystem]")
{
    const map<string, bool> testCases = {
            {"C:\\foo\\bar.txt", true},
            {"C:\\foo\\.bar",    true},
            {"C:\\foo\\bar\\",   true},
            {"C:\\foo\\.",       true},
            {"C:\\foo\\..",      true},
            {".",                false},
            {"..",               false},
            {"C:\\",             true},
            {"C:\\host",         true},
            {"C:\\/host",        true},
            {"C:\\//host",       true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).is_absolute();
        CHECK_MESSAGE((output == it->second),
                      "is_absolute '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output)
                                      << "'");
    }
}

/*!
 * Testing force_absolute_path()
 */
TEST_CASE("Test force_absolute_path", "[Validator]")
{
    map<string, vector<string>> testCases;
    testCases["cmake"] = {"C:\\", "cmake.exe"};
    testCases["..\\CMakeLists.txt"] = {"C:\\", "..\\CMakeLists.txt"};
    testCases["asdasdasdasdasdadasdas"] = {"C:\\", "asdasdasdasdasdadasdas"};
    testCases["."] = {"C:\\", "."};
    testCases["C:\\"] = {"C:\\", "C:\\"};
    testCases["C:\\asdasdasd"] = {"C:\\asdasdasd", "C:\\asdasdasd"};
    testCases["%HomeDrive%%HomePath%"] = {"C:\\", ""};
    testCases["%HomeDrive%%HomePath%\\"] = {"C:\\", ""};
    filesystem::path output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).force_absolute_path();
        REQUIRE_MESSAGE(!output.empty(), "force_absolute_path '" << it->first << "' -> '" << output << "'");
        CHECK_MESSAGE(output.startsWith(it->second[0]), "force_absolute_path s'" << it->first << "' -> '" << output << "'");
        CHECK_MESSAGE(output.endsWith(it->second[1]), "force_absolute_path e'" << it->first << "' -> '" << output << "'");
    }
}

/*!
 * Testing is_executabe()
 */
TEST_CASE("Test is_executabe", "[FileSystem]")
{
    const map<string, bool> testCases = {
            {"cmake",                true},
            {"C:\\foo\\.bar",        false},
            {"C:\\foo\\bar\\",       false},
            {"C:\\foo\\.",           false},
            {"C:\\foo\\..",          true}, // funny, this is a legal path on wondows OS
            {"C:\\foo\\bar\\..\\..", true}, // funny, this is a legal path on wondows OS
            {".",                    true},
            {"..",                   true},
            {"C:\\",                 true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).is_executabe();
        CHECK_MESSAGE((output == it->second),
                      "is_executabe '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output)
                                       << "'");
    }
}

/*!
 * Testing exists()
 */
TEST_CASE("Test exists", "[FileSystem]")
{
    const map<string, bool> testCases = {
            {"cmake",                true},
            {"C:\\foo\\.bar",        false},
            {"C:\\foo\\bar\\",       false},
            {"C:\\foo\\.",           false},
            {"C:\\foo\\..",          true}, // funny, this is a legal path on wondows OS
            {"C:\\foo\\bar\\..\\..", true}, // funny, this is a legal path on wondows OS
            {".",                    true},
            {"..",                   true},
            {"C:\\",                 true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::exists(filesystem::path(it->first).force_absolute_path());
        CHECK_MESSAGE((output == it->second),
                      "exists '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output)
                                 << "'");
    }
}

/*!
 * Testing get_environment_variable()
 */
TEST_CASE("Test get_environment_variable", "[FileSystem]")
{
    auto output = filesystem::get_environment_variable("PATH");
    REQUIRE_MESSAGE(!output.empty(), "PATH: '" << output << "'");
}

/*!
 * Testing _getSystemPaths()
 */
TEST_CASE("Test _getSystemPaths", "[FileSystem]")
{
    auto output = filesystem::_getSystemPaths();
    REQUIRE_MESSAGE(output.size() > 1, "PATHs: '" << output.size() << "'");
}
