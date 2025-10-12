#ifndef MEMORY_STAT_PROCESSING_H
#define MEMORY_STAT_PROCESSING_H

#include "../nlohmann/json.hpp"
#include <filesystem>
#include <unordered_map>

class ProcessObj; // forward declaration opplication object,

class MemoryStatProcessing
{
public:
    /**
     * @brief Constructs the shared pointer to the process algorithm and a struct that is consantly updated
     *
     * @param std::shared_ptr<ProcessALgorithm>
     * @return void
     */
    MemoryStatProcessing();


    /**
     * @brief parses the stat_sheet in json format.
     * @param filepath
     */
    std::unordered_map<std::string, double> evaluate_memory_stat_sheet(std::string filepath);

    /**
     * @brief handle data relating to the standard memory metrics relating to "byte size".
     * @param key_value
     * @param stat_sheet (passed as reference)
     */
    std::unordered_map<std::string, double>& size_metrics_data(nlohmann::json &page, std::unordered_map<std::string, double> &stat_sheet);

    /**
     * @brief handle data relating to protected keys
     * @param key_value
     * @param stat_sheet (passed as reference)
     */
    std::unordered_map<std::string, double>& protected_keys_data(std::string key_value, std::unordered_map<std::string, double> &stat_sheet);

    /**
     * @brief handle data relating to THP Eligibilty
     * @param std::string key_value
     * @param stat_sheet (passed as reference)
     */
    std::unordered_map<std::string, double>& thp_eligibility_data(std::string key_value, std::unordered_map<std::string, double> &stat_sheet);

    /**
     * @brief takes the data obtained from evaluate_memory_stat sheet and passes it to the specified application object.
     * @param std::unique_ptr<ApplicationObj> application
     */
    std::unordered_map<std::string, double> update_process_statistics(std::unique_ptr<ProcessObj> &process, std::unordered_map<std::string, double> stat_sheet);
};

#endif // CALCULATE_RAM_H
