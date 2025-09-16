#ifndef MEMORY_STAT_PROCESSING_H
#define MEMORY_STAT_PROCESSING_H

#include "../nlohmann/json.hpp"
#include <filesystem>
#include <unordered_map>

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

    std::unordered_map<std::string, double> get_stat_sheet()
    {
        return this->stat_sheet;
    }

    /**
     * @brief fully updates the current stat sheet (usually only need to do this once).
     * @param new_stat_sheet
     */
    void update_stat_sheet(std::unordered_map<std::string, double> new_stat_sheet)
    {
        this->stat_sheet = new_stat_sheet;
    }

    /**
     * @brief compares incoming stat_sheet with existing stat_sheet if it exists.
     * @param new_stat_sheet
     */
    bool compare_incoming_statistics(std::unordered_map<std::string, double> new_stat_sheet)
    {
        return new_stat_sheet == this->stat_sheet;
    }

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
    void update_application_statistics(std::unique_ptr<ApplicationObj> &app, std::unordered_map<std::string, double> stat_sheet);

private:
    std::unordered_map<std::string, double> stat_sheet;
};

#endif // CALCULATE_RAM_H
