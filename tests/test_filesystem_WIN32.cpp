/**
 * Created by Peter Hofmann on 07.01.19.
 */

#define CATCH_CONFIG_MAIN  // Tells Catch to provide a main()
//#define CHECK_MESSAGE(cond, msg) do { std::cout << msg); CHECK(cond); } while((void)0, 0)
//#define REQUIRE_MESSAGE(cond, msg) do { std::cout << msg); REQUIRE(cond); } while((void)0, 0)

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
            {"C:\\foo\\bar\\",    "bar"},
            {"C:\\foo\\.",       "."},
            {"C:\\foo\\..",      ".."},
            {".",            "."},
            {"..",           ".."},
            {"C:\\",            ""},
            {"C:\\host",        "host"},
            {"C:\\\\host",       "host"},
            {"C:\\\\\\host",      "host"}
    };

    string output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).filename();
        CHECK(output == it->second);
//        CHECK_MESSAGE(output == it->second, "basename '" << it->first << "' -> '" << it->second << "' : '" << output << "'");
//        std::cout << "basename '" << it->first << "' -> '" << it->second << "' : '" << output << "'";
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
            {"C:\\foo\\bar\\",    "C:\\foo"},
            {"C:\\foo\\.",       "C:\\foo"},
            {"C:\\foo\\..",      "C:\\foo"},
            {".",            ""},
            {"..",           ""},
            {"C:\\",            "C:\\"},
            {"C:\\host",        "C:\\"},
            {"C:\\\\host",       "C:\\"},
            {"C:\\\\\\host",      "C:\\"}
    };

    string output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).parent_path();
        CHECK(output == it->second);
//        CHECK_MESSAGE(output == it->second, "dirname '" << it->first << "' -> '" << it->second << "' : '" << output << "'");
//        std::cout << "dirname '" << it->first << "' -> '" << it->second << "' : '" << output << "'";
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
            {"C:\\foo\\bar\\",    true},
            {"C:\\foo\\.",       true},
            {"C:\\foo\\..",      true},
            {".",            false},
            {"..",           false},
            {"C:\\",            true},
            {"C:\\host",        true},
            {"C:\\/host",       true},
            {"C:\\//host",      true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).is_absolute();
        CHECK(output == it->second);
//        CHECK_MESSAGE((output == it->second), "is_absolute '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'");
//        std::cout << "is_absolute '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'";
    }
}

/*!
 * Testing get_full_path()
 */
TEST_CASE("Test get_full_path", "[Validator]")
{
    map<string, vector<string>> testCases;
    testCases["cmake"] = {"C:\\", "cmake"};
    testCases["../CMakeLists.txt"] = {"C:\\", "..\\CMakeLists.txt"};
    testCases["asdasdasdasdasdadasdas"] = {"C:\\", "asdasdasdasdasdadasdas"};
    testCases["."] = {"C:\\", "."};
    testCases["C:\\"] = {"C:\\", "C:\\"};
    testCases["C:\\asdasdasd"] = {"C:\\asdasdasd", "C:\\asdasdasd"};
    testCases["%HomeDrive%%HomePath%"] = {"C:\\", ""};
    testCases["%HomeDrive%%HomePath%\\"] = {"C:\\", ""};
    filesystem::path output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).get_full_path();
        REQUIRE(!output.empty());
        CHECK(output.startsWith(it->second[0]));
        CHECK(output.endsWith(it->second[1]));
//        REQUIRE_MESSAGE(!output.empty(), "get_full_path '" << it->first << "' -> '" << output << "'");
//        CHECK_MESSAGE(output.startsWith(it->second[0]), "get_full_path '" << it->first << "' -> '" << output << "'");
//        std::cout << output.startsWith(it->second[0]), "get_full_path '" << it->first << "' -> '" << output << "'";
    }
}

/*!
 * Testing is_executabe()
 */
TEST_CASE("Test is_executabe", "[FileSystem]")
{
    const map<string, bool> testCases = {
            {"cmake", true},
            {"C:\\foo\\.bar",    false},
            {"C:\\foo\\bar\\",    false},
            {"C:\\foo\\.",       false},
            {"C:\\foo\\..",      false},
            {".",            true},
            {"..",           true},
            {"C:\\",            true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).is_executabe();
        CHECK(output == it->second);
//        CHECK_MESSAGE((output == it->second), "is_executabe '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'");
//        std::cout << "is_executabe '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'";
    }
}

/*!
 * Testing exists()
 */
TEST_CASE("Test exists", "[FileSystem]")
{
    const map<string, bool> testCases = {
            {"cmake", true},
            {"C:\\foo\\.bar",    false},
            {"C:\\foo\\bar\\",    false},
            {"C:\\foo\\.",       false},
            {"C:\\foo\\..",      false},
            {".",            true},
            {"..",           true},
            {"C:\\",            true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::exists(filesystem::path(it->first).get_full_path());
        CHECK(output == it->second);
//        CHECK_MESSAGE((output == it->second), "exists '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'");
//        std::cout << "exists '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'";
    }
}
