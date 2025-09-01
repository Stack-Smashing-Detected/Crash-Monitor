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

    void set_application_identification_data(std::unordered_map<std::string, std::string> applications)
    {
        this->applications = applications;
    }

    std::unordered_map<std::string, std::string> get_application_identification_data()
    {
        return this->applications;
    }

    /**
     * Traverses through the "/proc" directory and stores all user owned PID directory names and symlinks
     *
     * @param: DIR
     * @return: std::vector<std::string>
     */
    void find_processes(DIR *dir);

    /**
     * Get the name of an application based on its process.
     */
    std::string find_process_name(std::string pid);

    /**
     * using the symlinks we obtained from the findProcesses function we can find our application names
     *
     * @param: std::vector<std::string>
     * @return: std::vector<std::string>
     */
    std::unordered_map<std::string, int> get_application_names(std::vector<std::string> processIndexes);

    /** Algorithm for finding Application Logos for better UI/UX
    std::vector<std::string> getApplicationLogoPaths(std::vector<std::string> processSymlinks);
    */

    /**
     * @brief Opens smaps file for each of the process PIDs provided so it can be parsed into JSON format
     *
     * @param std::vector<std::string>
     * @return void
     */
    void open_smaps(std::vector<std::string> processIndexes);

    /**
     * @brief opens an smap file for a single process
     *
     * @param std::string pid
     * @return void
     */
    void open_smap(std::string pid);
    /**
     * @brief Parses through the provided smap file, should pass by reference as the vector will be updated through this function.
     *
     * @param std::vector<std::string> pids
     * @return void
     */
    void parse_smap(std::ifstream &smap, std::string pid);

    /**
     * @brief incoming smaps data is not consistent so validation is required to ensure seamless transfer of data to json file.
     * @return std::string
     */
    std::string validate_incoming_data(std::vector<std::string> tokens);

private:
    std::unordered_map<std::string, std::string> applications; // a map of pids and their filepaths to the processes' executables
};
#endif // PROCESS_ALGORITHMS_H
