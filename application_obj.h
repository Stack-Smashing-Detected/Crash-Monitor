#ifndef APPLICATION_OBJ_H
#define APPLICATION_OBJ_H

#include
#include <string>

class ApplicationObj
{
public:
    ApplicationObj();

    std::string getApplicationName(){
        return this->applicationName;
    }

    // get the latest RAM usage reading
    int getRamUsage(){
        return ramUsage;
    }

    // update the RAM usage metric
    void updateRamUsage(int ram){
        this->ramUsage = ram;
    }

    // get the latest CPU usage reading
    int getCpuUsage(){
        return cpuUsage;
    }

    // update the CPU usage metric
    void updateCpuUsage(int cpu){
        this->cpuUsage = cpu;
    }

    // gets the current number of active spawned processes for this application
    int getSpawnedProcesses(){
        return spawnedProcesses;
    }

    // updates the current number of active spawned processes for this application
    void updateSpawnedProcesses(int spawnedProcesses){
        this->spawnedProcesses = spawnedProcesses;
    }

private:

    std::string applicationName;
    int spawnedProcesses;

    // the statistics of an application's overall memory use footprint.
    struct MemoryStats{
        size_t size = 0; // total mapping in kilobytes.
        size_t page_size_kernel = 0; // page size used by the kernel for mapping
        size_t page_size_MMU = 0; // page size as seen by the CPU
        size_t Rss = 0; // Resident set size, the size of all pages that this process has been mapped to.
        size_t Pss = 0; // private memory share, the amount of memory owned by the process across all memory mappings
        size_t shared_clean = 0; // proportion of unmodified memory within the resident page
        size_t shared_dirty = 0; // proportion of modified memory within the resident page
        size_t private_clean = 0; // proportion of unmodified private memory owned by the process
        size_t private_dirty = 0; // proportion of modified memory owned by the process
        size_t referenced = 0; // memory recently used/accessed
        size_t anonymous = 0; // memory not backed by any file
        size_t ksm = 0; // kernel same-page merging
        size_t lazy_free = 0; // marked memory that the kernel can easily reclaim, it is marked with the status MADV_FREE
        size_t anon_huge_pages = 0; // anonymous memory pages marked "Huge"
        size_t shmem_pmd_mapped = 0; // Shared memory using "page middle directory" hugepages
        size_t fil_pmd_mapped = 0; // File backed PMD hugepages
        size_t shared_huget_lb = 0; // Memory mapped from hugetlbfs and shared;
        size_t private_huget_lb = 0; // Memory mapped from hugetlbfs but only for the current process;
        size_t swap = 0; // amount of swap memory used by the page;
        size_t swap_pss = 0; // process' proportion of swap memory within the page
        size_t locked = 0; // locked memory that cannot be moved to swap'

        /**
         * @brief constructor for memory stats struct
         */
        MemoryStats(){}

        /**
        * @brief uses a switch case to update the struct accordingly
        *
        * @param std::string
        * @param int
        * @return void;
        */
        void update_statistic(std::string metric, int metric_value);

};

#endif // APPLICATION_OBJ_H
