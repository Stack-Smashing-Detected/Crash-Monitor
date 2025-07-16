#ifndef PROCESS_ALGORITHMS_H
#define PROCESS_ALGORITHMS_H

#include <algorithm>
#include <stdexcept>
#include <cerrno>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <format>
#include <dirent.h>


/**
 * A library class for finding application data that does not require constant monitoring.
 *
 */
class ProcessAlgorithms
{

public:
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

    /**
    * Traverses through the "/proc" directory and stores all user owned PID directory names and symlinks
    *
    * @param: DIR
    * @return: std::vector<std::string>
    */
    void findProcesses(DIR *dir);

    /**
    * using the symlinks we obtained from the findProcesses function we can find our application names
    *
    * @param: std::vector<std::string>
    * @return: std::vector<std::string>
    */
    std::unordered_map<std::string, int> getApplicationNames(std::vector<std::string> processIndexes);

    /** Algorithm for finding Application Logos for better UI/UX
    std::vector<std::string> getApplicationLogoPaths(std::vector<std::string> processSymlinks);
    */

    /**
     * @brief Opens smaps file for each of the process PIDs provided so it can be parsed into JSON format
     *
     * @param std::vector<std::string>
     * @return void
     */
    void openSmaps(std::vector<std::string> processIndexes);


    /**
    * @brief Parses through the provided smap file, should pass by reference as the vector will be updated through this function.
    *
    * @param std::vector<std::string> pids
    * @return void
    */
    void parseSmap(std::ifstream &smap, std::string pid);

    /**
    * @brief incoming smaps data is not consistent so validation is required to ensure seamless transfer of data to json file.
    * @return std::string
    */
    std::string validateIncomingData(std::vector<std::string> tokens);

private:
    std::vector<std::string> processList;
    std::vector<std::string> processSymlinks; // a list of filepaths to the processes' executables, known as symbolic links.
};

#endif // PROCESS_ALGORITHMS_H
