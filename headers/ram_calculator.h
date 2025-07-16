#ifndef CALCULATE_RAM_H
#define CALCULATE_RAM_H

#include <filesystem>
#include <fstream>
#include <vector>


class RamCalculator{
public:
    /**
    * @brief Constructs the shared pointer to the process algorithm and a struct that is consantly updated
    *
    * @param std::shared_ptr<ProcessALgorithm>
    * @return void
    */
    RamCalculator();

    /**
     * @brief given a process identifier it will calculate the memory usage metric.
     * @param std::string pid
     */
    void evaluate_memory_stat_sheet(std::string pid);

    /**
     * @brief takes the data obtained from evaluate_memory_stat sheet and passes it to the specified application object.
     * @param std::vector<std::pair> mem_stats
     * @param std::string pid
     */
    void update_application_statistics(std::string pid);
};


#endif // CALCULATE_RAM_H
