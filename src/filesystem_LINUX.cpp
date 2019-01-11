/**
 * Created by Peter Hofmann on 09.01.19.
 */

#include <unistd.h>
#include <vector>
#include <stdexcept>
#include "filesystem.h"

namespace filesystem
{
    /**
     * Constructor with no pathing argument
     */
    path::path()
            : std::string(), _directoryDelimiter('/') {}

    /**
     * Constructor with file or folder location parameter
     * @param location - file or folder location
     */
    path::path(const path &location) : std::string(location), _directoryDelimiter('/')
    {
        _rstrip();
    }

    /**
     * Constructor with file or folder location parameter
     * @param location - file or folder location
     */
    path::path(const std::string &location) : std::string(location), _directoryDelimiter('/')
    {
        _rstrip();
    }

    std::string path::root_name()
    {
        return "";
    }

    std::string path::root_directory()
    {
        if (front() == _directoryDelimiter)
            return std::string(1, _directoryDelimiter);
        return "";
    }

    /**
     * Return if current path includes the root path
     * @return
     */
    bool path::is_absolute()
    {
        return has_root_directory();
    }

    /**
     * Get the full path of any file or directory
     *
     * This method tries to forcefully a absolute path for the current path.
     * Relative paths are looked up locally, then in the system paths.
     * TODO:
     *  expandvars - Replace all environment variables
     *  normpath   - Collapsing redundant separators
     *  realpath   - Eliminating any symbolic links encountered in the path
     *
     * @param path - Directory path or file path
     * @return - full path to location
     */
    path path::force_absolute_path()
    {
        filesystem::path systemPath, possiblePath;
        std::vector<std::string> systemPathVector;

        if (this->empty())
            return filesystem::path("");

        filesystem::path location(*this);
        /// expanduser
        std::string homeVariable = "~";
        if (startsWith(homeVariable))
        {
            location = get_environment_variable("HOME") + substr(homeVariable.size());
        }

        filesystem::path parentPath = location.parent_path();
        filesystem::path fileName = location.filename();
//    std::cout << "'"<< parentPath << "' + '" << fileName << "'" << std::endl;

        /// Path is fullPath, beware: read_symlink, is_symlink
        if (parentPath.is_absolute())
            return parentPath / fileName;

        possiblePath = filesystem::current_path() / location;
        /// Existing CWD + relative path
        if (filesystem::exists(possiblePath))
            return possiblePath;


        /// check if it is an executable, found in a system path
        if (parentPath.empty() && !fileName.is_absolute() && !filesystem::exists(fileName))
        {
            systemPathVector = _getSystemPaths();
            for (auto systemPathIt = systemPathVector.begin(); systemPathIt < systemPathVector.end(); systemPathIt++)
            {
                // strip('"') ???
                systemPath = filesystem::path(*systemPathIt);
                if (filesystem::is_regular_file(systemPath / fileName))
                {
                    return systemPath / fileName;
                }
            }
        }
        /// CWD + relative path, no file or folder at path
        return possiblePath;
    }

    /**
     * Tests if a file or directory has permissions to be executed
     * @return True if executable
     */
    bool path::is_executabe()
    {
        auto fullPath = force_absolute_path();
        return access(fullPath.c_str(), X_OK) == 0;
    }

    /**
     * This splits a string
     * Splitting of the string at a specific delimiter results into multiple strings that are returned as a vector.
     * @param input - String to be split
     * @param delimiter - Positions at which input is split, excluding the delimiter.
     * @return - Vector of Strings
     */
    inline std::vector<std::string> _explode(std::string const &input, char delimiter)
    {
        std::vector<std::string> result;
        std::istringstream iss(input);

        for (std::string token; std::getline(iss, token, delimiter);)
        {
            result.push_back(std::move(token));
        }

        return result;
    }

    /// OS specific delimiter used in the PATH environment variable
    const char pathDelimiter = ':';

    /**
     * Returning list of system paths
     * Reading the PATH environment variable, a list of those paths is returned.
     * @return - Vector of Strings, each representing a system path.
     */
    std::vector<std::string> _getSystemPaths()
    {
        std::string systemPath;
        systemPath = get_environment_variable("PATH");
        return _explode(systemPath, pathDelimiter);
    }

    /**
     * Get current working directory.
     * @return - Current Working Directory
     */
    path current_path()
    {
        char buff[FILENAME_MAX];
        getcwd(buff, FILENAME_MAX);
        return path(std::string(buff));
    }

    /**
     * Get the environment variable
     * Resolve the environment variable and return it as String
     * @return - Home directory path
     */
    std::string get_environment_variable(std::string const &input)
    {
        const char *variable = getenv(input.c_str());
        if (variable == NULL)
            return path("");
        return std::string(variable);
    }
}
