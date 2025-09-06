#ifndef APPLICATION_OBJ_H
#define APPLICATION_OBJ_H

// unordered_map is already included in memory_stat_processing.h
#include "../headers/memory_stat_processing.h"
#include "../headers/process_obj.h"
#include <string>

class ApplicationObj
{
public:
    // an enum class for all the size_t metric
    ApplicationObj(std::string name);

    // s

    std::string get_application_name()
    {
        return this->application_name;
    }

    bool match_search(std::string name)
    {
        if (name == this->application_name)
            return true;

        return false;
    }

    /**
     * @brief registers a process with this application, the process object itself is created in the App Manager
     * and then its ownership is changed to this application object through "move semantics"
     * @param pid -> the pid of an discovered process.
     */
    void register_process(std::unique_ptr<ProcessObj> discovered_process);

    /**
     * @brief validates input and obtains get a specific statistic from the object through string matching if no match it will pass a value of -1
     * to the application manager which will output an informative error to the user. For more information refer to "application_manager.h & application_manager.cpp"
     * @param statistic
     */
    int get_mem_statistic(std::string statistic);

    /**
     * @brief update the memory usage statistics of this particular application
     * (either whole new process or changes in existing process memory usage);
     * @param statistic
     * @param amount -> the amount in kB(kilobytes) i.e. 4kB = 4096 bytes or size_t value of 4096
     */
    void update_mem_statistics(std::unordered_map<std::string, double> stat_changes);

private:
    std::vector<std::unique_ptr<ProcessObj>> owned_processes;
    std::string application_name;
    // the statistics of an application's overall memory use footprint.
    std::unordered_map<std::string, int> app_mem_statistics;
};

#endif // APPLICATION_OBJ_H
