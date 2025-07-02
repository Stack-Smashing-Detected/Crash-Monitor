#include "../headers/process_algorithms.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

// constructor, sets up the process list and process symlinks for use later.
ProcessAlgorithms::ProcessAlgorithms(DIR *dir)
{
    ProcessAlgorithms::findProcesses(dir);
}

// default constructor
ProcessAlgorithms::ProcessAlgorithms() {}

/**
 * Traverses through the "/proc" directory and stores all user owned PID directory names and symlinks
 *
 * @params: DIR
 * @return: std::vector<std::string>
 */
void ProcessAlgorithms::findProcesses(DIR *dir)
{
    std::vector<std::string> foundProcesses;
    std::vector<std::string> processSymlinks;

    if (!(dir = opendir("/proc")))
    {
        throw std::runtime_error("failed to open process list");
    }

    while (dirent *dirp = readdir(dir))
    {
        // check if it is directory
        if (dirp->d_type != DT_DIR)
            continue;

        // are character names a digit? Processes names are all identified by PIDs.
        if (!std::all_of(dirp->d_name, dirp->d_name + strlen(dirp->d_name),
                         [](char c)
                         { return std::isdigit(c); }))
            continue;

        // convert the c-string into a std::string
        std::string pid(dirp->d_name);
        // filter out the user owned PIDs using std::filesystem::read_symlink()'s error handling. Any PID owned by the system i.e. root will throw an exception via "readlink()"
        // which is implemented in "read_symlink", this exception should be caught as "filesystem::error" which would stop it from being added to our lists.

        try{
            std::stringstream filepathStream;
            filepathStream << "/proc/" << pid << "/exe";
            std::string exePath = filepathStream.str();

            processSymlinks.push_back(std::filesystem::read_symlink(exePath).string());
            foundProcesses.push_back(pid);

        }catch(std::filesystem::filesystem_error fe){
            continue;
        }
    }
    if (closedir(dir))
        throw std::runtime_error(std::strerror(errno));

    // finally set the newly populated data structures so we can use them later.
    this->setProcessList(foundProcesses);
    this->setSymLinksList(processSymlinks);
}

/**
 * using the symlinks we obtained from the findProcesses function we can find our application names
 *
 * @params: std::vector<std::string>
 * @return: std::vector<std::string>
 */
std::unordered_map<std::string, int> ProcessAlgorithms::getApplicationNames(std::vector<std::string> processSymlinks)
{
    // a list of application names and occurences of application name i.e the number of processes per application.
    std::unordered_map<std::string, int> appNames;

    for (std::string &symlink : processSymlinks)
    {
        auto const& pos = symlink.find_last_of('/');
        std::string appName = symlink.substr(pos + 1);

        int procCount = 1;
        auto const& result = appNames.try_emplace(appName, procCount);

        if(!result.second){
            result.first->second += 1;
        }
    }

    return appNames;
}



