#ifndef MEMORY_STAT_PROCESSING_H
#define MEMORY_STAT_PROCESSING_H

#include <filesystem>
#include <unordered_map>
#include <memory>

class ApplicationObj; // forward declaration opplication object,

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

    std::unordered_map<std::string, int> get_stat_sheet()
    {
        return this->stat_sheet;
    }

    /**
     * @brief parses the stat_sheet in json format.
     * @param std::string pid
     */
    void evaluate_memory_stat_sheet(std::filesystem::path filepath);

    /**
     * @brief handle data relating to protected keys
     * @param std::string key_value
     * @param std::unordered_map<std::string, int>
     */
    std::unordered_map<std::string, int> protected_keys_data(std::string key_value, std::unordered_map<std::string, int> &stat_sheet);

    /**
     * @brief handle data relating to THP Eligibilty
     * @param std::string key_value
     * @param std::unordered_map<std::string, int>
     */
    std::unordered_map<std::string, int> thp_eligibility_data(std::string key_value, std::unordered_map<std::string, int> &stat_sheet);

    /**
     * @brief handle data relating to the standard memory metrics relating to "byte size".
     * @param std::string key_value
     * @param std::unordered_map<std::string, int>
     */
    std::unordered_map<std::string, int> size_metrics_data(std::string key, std::string key_value, std::unordered_map<std::string, int> &stat_sheet);

    /**
     * @brief takes the data obtained from evaluate_memory_stat sheet and passes it to the specified application object.
     * @param std::unique_ptr<ApplicationObj> application
     */
    void update_application_statistics(ApplicationObj &application);

private:
    std::unordered_map<std::string, int> stat_sheet;
};

#endif // CALCULATE_RAM_H
