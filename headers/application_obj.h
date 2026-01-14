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


    std::string get_application_name()
    {
        return this->application_name;
    }

    /**
     * @brief Checks if the incoming name matches the name of the application instance.
     */
    bool match_search(std::string name)
    {
        if (name == this->application_name)
            return true;

        return false;
    }

    /**
     * @brief returns a reference to the application object instance's memory statsheet.
     * @return std::unordered_map<std::string, double>&
     */
    std::unordered_map<std::string, double> &get_app_statsheet()
    {
        return this->app_mem_statistics;
    }

    /**
     * @brief returns a reference to the owned processes container
     * @return std::vector<std::unique_ptr<ProcessObj>>&
     */
    std::vector<std::unique_ptr<ProcessObj>>& get_owned_processes()
    {
        return this->owned_processes;
    }

    /**
     * @brief get a specific stat's value from the stat sheet.
     * @param statistic -> std::string
     * @return double
     */
    double get_specific_stat(std::string statistic);

    /**
     * @brief update the memory usage statistics of this particular application
     * (either whole new process or changes in existing process memory usage);
     * @param statistic
     * @param amount -> the amount in kB(kilobytes) i.e. 4kB = 4096 bytes or size_t value of 4096
     */
    void update_mem_statistics(std::unordered_map<std::string, double> stat_changes);

    /**
     * @brief registers a process with this application, the process object itself is created in the App Manager
     * and then its ownership is changed to this application object through "move semantics". The process' stat sheet is also
     * added to the application's own stat_sheet.
     * @param pid -> the pid of an discovered process.
     */
    void register_process(std::unique_ptr<ProcessObj> discovered_process);

private:
    std::vector<std::unique_ptr<ProcessObj>> owned_processes;
    std::string application_name;
    // the statistics of an application's overall memory use footprint.
    std::unordered_map<std::string, double> app_mem_statistics;
};

#endif // APPLICATION_OBJ_H
