/**
 * Created by Peter Hofmann on 09.01.19.
 */

#ifndef VALIDATOR_FILESYSTEM_H
#define VALIDATOR_FILESYSTEM_H

#include <sys/stat.h>
#include <sstream>
#include <string>
#include <vector>

/**
 * filesystem.h
 *
 * Emulates '<experimental/filesystem>' without the need for g++17 and additional libraries.
 * Not all methods are implemented as they are made as they are needed.
 * Some additional methods are available, such as get_full_path().
 */
namespace filesystem
{
    class path : public std::string
    {
    private:
        const char _directoryDelimiter;
        std::string _root_name;
        std::string _root_directory;

        /**
         * Remove all delimiter at the end of the string
         */
        void _rstrip()
        {
            size_type rootPathSize = root_path().size();
            while (this->size() > rootPathSize && this->back() == _directoryDelimiter)
                this->pop_back();
        }

        void _init_root();

    public:
        path();

        path(const path &location);

        path(const std::string &location);

        bool is_absolute();

        bool is_executabe();

        /**
         * Overwrite current path with another
         * @param location - Directory or file path
         * @return - New Path
         */
        path operator=(const path &location)
        {
            return std::string::operator=(std::string(location.c_str()));
        }

        /**
         * Concatenation of paths, separated with a directory delimiter.
         * @param location - Directory or file path
         * @return - New Path
         */
        path operator/(const path &location)
        {
            if (this->empty())
                return location;
            if (location.empty())
                return *this;
            if (this->back() == _directoryDelimiter)
                return this->string() + std::string(location.c_str());
            return this->string() + std::string(1, _directoryDelimiter) + std::string(location.c_str());
        }

        /**
         * Get method for _root_name
         * Unix: ''
         * Windows: 'C:'
         * @return - Root of path
         */
        std::string root_name() { return _root_name; }

        /**
         * Get method for _root_directory
         * Unix: '/'
         * Windows: '\'
         * @return - Root directory
         */
        std::string root_directory() { return _root_directory; }

        /**
         * Get method for root path
         * Root name + root directory
         * Unix: '/'
         * Windows: 'c:\'
         * @return - Root Path
         */
        path root_path() { return root_name() + root_directory(); }

        /**
         * Check if path has a root name.
         * Linux: Always false.
         * Windows: True, if absolute path
         */
        bool has_root_name() { return !root_name().empty(); }

        /**
         * Check if path has a root directory.
         * Linux: True, if absolute path
         * Windows: True, if absolute path
         */
        bool has_root_directory() { return !root_directory().empty(); }

        /**
         * Check if path has a root path.
         * Linux: True, if absolute path
         * Windows: True, if absolute path
         */
        bool has_root_path() { return has_root_name() || has_root_directory(); }

        /**
         * Check if path starts with a specific string
         * @param value - Value tested against path
         * @return - True if path is sub string of value at the beginning
         */
        bool startsWith(const std::string &value)
        {
            return rfind(value, 0) == 0;
        }

        /**
         * Check if path ends with a specific string
         * @param value - Value tested against path
         * @return - True if path is sub string of value at the end
         */
        bool endsWith(const std::string &value)
        {
            if (length() < value.length())
                return false;
            return (0 == compare(length() - value.length(), value.length(), value));
        }

        /**
         * Same as 'basename'
         * Return the folder or file name without the rest of the path
         * @return - Folder or file name
         */
        path filename()
        {
            size_type delimiterPosition = this->rfind(_directoryDelimiter);
            if (delimiterPosition == std::string::npos)
                return *this;
            return this->substr(delimiterPosition + 1);
        }

        /**
         * Same as 'dirname'
         * Return the parent folder path without the last path element
         * @return - Parent folder path
         */
        path parent_path()
        {
            size_type delimiterPosition = this->rfind(_directoryDelimiter);

            /// No parent folder
            if (delimiterPosition == std::string::npos)
                return path("");
            path result = this->substr(0, delimiterPosition);

            /// Is at root
            if (result.empty())
                return root_path();
            result._rstrip();

            /// Parent folder
            return result;
        }

        path get_full_path();

        /**
         * Return copy of path as string obj.
         * @return
         */
        std::string string() { return std::string(this->c_str()); }
    };

    /**
     * Check if a file or folder exists at the path location
     * @param location - File or folder path
     * @return - True if file or folder exists at the path location
     */
    inline bool exists(const path &location)
    {
        struct stat fileAttributes;
        return stat(location.c_str(), &fileAttributes) == 0;
    }

    /**
     * Check if there is a file at a location
     * @param location - File or folder path
     * @return  - True if file exists at the path location
     */
    inline bool is_regular_file(const path &location)
    {
        struct stat fileAttributes;
        if (stat(location.c_str(), &fileAttributes) != 0)
        {
            return false;
        }
        return (fileAttributes.st_mode & S_IFREG) != 0;
    }

    /**
     * Check if there is a folder at a location
     * @param location - File or folder path
     * @return  - True if folder exists at the path location
     */
    inline bool is_directory(const path &name)
    {
        struct stat fileAttributes;
        if (stat(name.c_str(), &fileAttributes) != 0)
            return false;
        return (fileAttributes.st_mode & S_IFDIR) != 0;
    }

    std::vector<std::string> _getSystemPaths();

    path current_path();

    path get_environment_variable(std::string const &input);

//    temp_directory_path
}

#endif //VALIDATOR_FILESYSTEM_H
