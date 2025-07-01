#ifndef PROCESS_ALGORITHMS_H
#define PROCESS_ALGORITHMS_H

#include <algorithm>
#include <stdexcept>
#include <cerrno>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <dirent.h>

/**
 * A library class for finding application data that does not require constant monitoring.
 *
 */
class ProcessAlgorithms
{

public:
    ProcessAlgorithms(DIR *dir); // setup directory
    ProcessAlgorithms();

    // mainly for using the listview during testing, will change regularly depending on what needs to be tested.
    std::vector<std::string> getProcessList()
    {
        return processList;
    }

    // mainly for testing the list views will change regularaly depending on what needs to be tested.
    void setProcessList(std::vector<std::string> processList)
    {
        this->processList = processList;
    }

    std::vector<std::string> getSymlinks()
    {
        return processSymlinks;
    }

    void setSymLinksList(std::vector<std::string> processSymlinks)
    {
        this->processSymlinks = processSymlinks;
    }

    // get all the process names we'll need this to access the process data
    // for displaying ram usage, cpu usage, application logos for UI enhancement etc.
    std::vector<std::string> findProcesses(DIR *dir);

    // Algorithm for finding the names of the application
    std::unordered_map<std::string, int> getApplicationNames(std::vector<std::string> processIndexes);

    // Algorithm for finding Application Logos for better UI/UX
    std::vector<std::string> getApplicationLogoPaths(std::vector<std::string> processIndexes);

private:
    std::vector<std::string> processList;
    std::vector<std::string> processSymlinks; // a list of filepaths to the processes' executables, known as symbolic links.
};

#endif // PROCESS_ALGORITHMS_H
