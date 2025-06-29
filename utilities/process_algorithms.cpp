#include "../headers/process_algorithms.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

// constructor, sets up the process list.
ProcessAlgorithms::ProcessAlgorithms(DIR *dir)
{
    std::vector<std::string> processList = ProcessAlgorithms::findProcesses(dir);
    ProcessAlgorithms::setProcessList(processList);
}

// default constructor
ProcessAlgorithms::ProcessAlgorithms() {}

/**
 * Traverses through the "/proc" directory and adds all PID directory names to a list.
 *  This PID list is essential in discovering data needed for the application to function.
 *
 * @params: DIR
 * @return: std::vector<std::string>
 */
std::vector<std::string> ProcessAlgorithms::findProcesses(DIR *dir)
{
    std::vector<std::string> foundProcesses;

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
        foundProcesses.push_back(pid);
    }
    if (closedir(dir))
        throw std::runtime_error(std::strerror(errno));

    return foundProcesses;
}

/**
 * using the PID list generated from the findProcesses function, a list of application names are extracted and emplaced
 * inside a vector data structure.
 *
 * @params: std::vector<std::string>
 * @return: std::vector<std::string>
 */
std::unordered_map<std::string, int> ProcessAlgorithms::getApplicationNames(std::vector<std::string> processIndexes)
{
    // open file at "/proc/processIndex[index]/comm";
    std::filebuf fb;

    // build path using stringsteam
    std::stringstream filepathStream;

    // a list of application names and occurences of application name i.e the number of processes per application.
    std::unordered_map<std::string, int> appNames;

    for (std::string &pid : processIndexes)
    {
        filepathStream << "/proc/" << pid << "/comm";
        std::string filepath = filepathStream.str();

        // extract the name out of the application
        std::ifstream ifs(filepath);
        if(ifs.is_open()){
            // get file contents
            std::string appName;
            std::getline(ifs, appName, '/');
            // adding the contents of "/proc/{pid}/comm" to name map
            int count = 1;
            auto [it, inserted] = appNames.try_emplace(appName, count);

            // if duplicate name found increase the value of "processes"
            if (!inserted)
            {
                it->second += 1;
            }
        }else {
            std::cout << "Error opening file";
        }
        // close the current filestream
        ifs.close();
        // reset string stream.
        filepathStream.str("");
        filepathStream.clear();
    }

    return appNames;
}

