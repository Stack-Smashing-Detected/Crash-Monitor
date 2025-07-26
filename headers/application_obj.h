#ifndef APPLICATION_OBJ_H
#define APPLICATION_OBJ_H

#include "../headers/memory_stat_processing.h"
#include <string>
#include <unordered_map>

class ApplicationObj
{
public:

    // an enum class for all the size_t metric
    ApplicationObj();

    std::string getApplicationName()
    {
        return this->applicationName;
    }

    // gets the current number of active spawned processes for this application
    int getSpawnedProcesses()
    {
        return spawnedProcesses;
    }

    // updates the current number of active spawned processes for this application
    void updateSpawnedProcesses(int spawnedProcesses)
    {
        this->spawnedProcesses = spawnedProcesses;
    }

    void update_protection_level(int protected_count, int unprotected_count);
    std::string get_current_protection_level(){
        return this->protection_level;
    }

    void update_thp_eligibility(int false_count, int true_count);
    std::string get_current_thp_eligibility_level(){
        return this->thp_eligibility;
    }

    /**
     * @brief update the memory usage statistics of this particular application
     * @param statistic
     * @param int amount -> the amount in kB(kilobytes) i.e. 4kB = 4096 bytes or size_t value of 4096
     */
    void update_mem_statistic(std::string statistic, int amount);

private:
    std::string applicationName;
    int spawnedProcesses;
    std::string protection_level;     // the percentage of pages with a non-zero protection key.
    std::string thp_eligibility;      // the percentage of pages that are "true" for the THPeligibility metric

    // the statistics of an application's overall memory use footprint.
    std::unordered_map<std::string, int> app_mem_statistics;
};

#endif // APPLICATION_OBJ_H
