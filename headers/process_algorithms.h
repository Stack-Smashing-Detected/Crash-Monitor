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

    /**
     * Traverses through the "/proc" directory and stores all user owned PID directory names and symlinks
     *
     * @param: DIR
     * @return: std::unordered_map<std::string, std::string>
     */
    std::unordered_map<std::string, std::string> find_processes();

    /**
     * @brief Finds a possible application name from a newly discovered process, this function is used only after the inital setup.
     * for initial setup functionality, refer to "find_processes" function.
     *
     * @param: pid -> std::string
     * @return: std::string
     */
    std::string find_process_name(std::string pid);



    /** Algorithm for finding Application Logos for better UI/UX
    std::vector<std::string> getApplicationLogoPaths(std::vector<std::string> processSymlinks);
    */

    /**
     * @brief Opens smaps file for each of the process PIDs provided so it can be parsed into JSON format
     *
     * @param std::vector<std::string>
     * @return void
     */
    void open_smaps(std::unordered_map<std::string, std::string> &processes);

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
     * @brief: Handles the name of the page, the line always starts with a hexadecimal number so we can check for that.
     * the data we're after is the
     */

    /**
     * @brief incoming smaps data is not consistent so validation is required to ensure seamless transfer of data to json file.
     * @return std::string
     */
    std::string validate_incoming_data(std::vector<std::string> tokens);

};
#endif // PROCESS_ALGORITHMS_H
