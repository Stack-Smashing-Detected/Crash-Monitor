#ifndef APPLICATION_OBJ_H
#define APPLICATION_OBJ_H

// unordered_map is already included in memory_stat_processing.h
#include "../headers/memory_stat_processing.h"
#include <string>

class ApplicationObj
{
public:
    // an enum class for all the size_t metric
    ApplicationObj(std::string pid, std::string name);

    std::string get_application_name()
    {
        return this->application_name;
    }

    void update_protection_level(int protected_count, int unprotected_count);
    std::string get_current_protection_level()
    {
        return this->protection_level;
    }

    void update_thp_eligibility(int false_count, int true_count);
    std::string get_current_thp_eligibility_level()
    {
        return this->thp_eligibility;
    }

    /**
     * @brief validates input and obtains get a specific statistic from the object through string matching if no match it will pass a value of -1
     * to the application manager which will output an informative error to the user. For more information refer to "application_manager.h & application_manager.cpp"
     * @param statistic
     */
    int get_mem_statistic(std::string statistic);

    /**
     * @brief update the memory usage statistics of this particular application
     * @param statistic
     * @param int amount -> the amount in kB(kilobytes) i.e. 4kB = 4096 bytes or size_t value of 4096
     */
    void update_mem_statistics(std::unordered_map<std::string, int> incoming_mem_data);

private:
    std::string application_pid;
    std::string application_name;
    std::string protection_level; // the percentage of pages with a non-zero protection key.
    std::string thp_eligibility;  // the percentage of pages that are "true" for the THPeligibility metric

    // the statistics of an application's overall memory use footprint.
    std::unordered_map<std::string, int> app_mem_statistics;
};

#endif // APPLICATION_OBJ_H
