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
            {"/foo/bar.txt", "bar.txt"},
            {"/foo/.bar",    ".bar"},
            {"/foo/bar/",    "bar"},
            {"/foo/.",       "."},
            {"/foo/..",      ".."},
            {".",            "."},
            {"..",           ".."},
            {"/",            ""},
            {"/host",        "host"},
            {"//host",       "host"},
            {"///host",      "host"}
    };

    string output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).filename();
        CHECK_MESSAGE(output == it->second, "basename '" << it->first << "' -> '" << it->second << "' : '" << output << "'");
    }
}

/*!
 * Testing parent_path()
 */
TEST_CASE("Test parent_path", "[FileSystem]")
{
    const map<string, string> testCases = {
            {"/foo/bar.txt", "/foo"},
            {"/foo/.bar",    "/foo"},
            {"/foo/bar/",    "/foo"},
            {"/foo/.",       "/foo"},
            {"/foo/..",      "/foo"},
            {".",            ""},
            {"..",           ""},
            {"/",            "/"},
            {"/host",        "/"},
            {"//host",       "/"},
            {"///host",      "/"}
    };

    string output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).parent_path();
        CHECK_MESSAGE(output == it->second, "dirname '" << it->first << "' -> '" << it->second << "' : '" << output << "'");
    }
}

/*!
 * Testing is_absolute()
 */
TEST_CASE("Test is_absolute", "[FileSystem]")
{
    const map<string, bool> testCases = {
            {"/foo/bar.txt", true},
            {"/foo/.bar",    true},
            {"/foo/bar/",    true},
            {"/foo/.",       true},
            {"/foo/..",      true},
            {".",            false},
            {"..",           false},
            {"/",            true},
            {"/host",        true},
            {"//host",       true},
            {"///host",      true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).is_absolute();
        CHECK_MESSAGE((output == it->second), "is_absolute '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'");
    }
}

/*!
 * Testing get_full_path()
 */
TEST_CASE("Test get_full_path", "[Validator]")
{
    map<string, vector<string>> testCases;
    testCases["cmake"] = {"/", "cmake"};
    testCases["../CMakeLists.txt"] = {"/", "../CMakeLists.txt"};
    testCases["asdasdasdasdasdadasdas"] = {"/", "asdasdasdasdasdadasdas"};
    testCases["."] = {"/", "."};
    testCases["/"] = {"/", "/"};
    testCases["/asdasdasd"] = {"/asdasdasd", "/asdasdasd"};
    testCases["~"] = {"/Users/", ""};
    testCases["~/"] = {"/Users/", ""};
    filesystem::path output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).get_full_path();
        REQUIRE_MESSAGE(!output.empty(), "get_full_path '" << it->first << "' -> '" << output << "'");
        CHECK_MESSAGE(output.startsWith(it->second[0]), "get_full_path '" << it->first << "' -> '" << output << "'");
    }
}

/*!
 * Testing is_executabe()
 */
TEST_CASE("Test is_executabe", "[FileSystem]")
{
    const map<string, bool> testCases = {
            {"cmake", true},
            {"/foo/.bar",    false},
            {"/foo/bar/",    false},
            {"/foo/.",       false},
            {"/foo/..",      false},
            {".",            true},
            {"..",           true},
            {"/",            true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::path(it->first).is_executabe();
        CHECK_MESSAGE((output == it->second), "is_executabe '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'");
    }
}

/*!
 * Testing exists()
 */
TEST_CASE("Test exists", "[FileSystem]")
{
    const map<string, bool> testCases = {
            {"cmake", true},
            {"/foo/.bar",    false},
            {"/foo/bar/",    false},
            {"/foo/.",       false},
            {"/foo/..",      false},
            {".",            true},
            {"..",           true},
            {"/",            true}
    };

    bool output;
    for (auto it = testCases.begin(); it != testCases.end(); it++)
    {
        output = filesystem::exists(filesystem::path(it->first).get_full_path());
        CHECK_MESSAGE((output == it->second), "exists '" << it->first << "' -> '" << to_string(it->second) << "' : '" << to_string(output) << "'");
    }
}
