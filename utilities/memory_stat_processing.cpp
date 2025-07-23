/**
 * Source file for the Ram Calculator
 *
 * Designed by Victor J Wilson
 * Github: Stack-Smashing-Detected
 **/

#include "../headers/memory_stat_processing.h"
#include "../nlohmann/json.hpp"
#include <cstddef>
#include <format>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <unordered_map>

MemoryStatProcessing::MemoryStatProcessing() {} // nothing needs to be setup since data is accessed from file.

void MemoryStatProcessing::evaluate_memory_stat_sheet(std::filesystem::path filepath)
{

    using json = nlohmann::json
        // read through the json file
        json j_array;
    std::ifstream stat_sheet(filepath.string());

    stat_sheet >> j_array;
    stat_sheet.close();

    std::unordered_map<std::string, int> stat_sheet = get_stat_sheet();
    // prepare unique elements for protection key metric
    int protected_count = 0;
    int unprotectecd_count = 0;

    // prepare unique elements for THP eligibility metric
    int true_count = 0;
    int false_count = 0;

    // add unique elements associated with ProtectionKey metric
    stat_sheet.emplace("Protected", protected_count);
    stat_sheet.emplace("Unprotected", unprotected_count);

    // add unique elements associated with THPeligible metric.
    stat_sheet.emplace("True", true_count);
    stat_sheet.emplace("False", false_count);

    for (auto &item : j_array.items())
    {
        json page = item.value();
        for (auto &page_key : page.items)
        {
            // handle "ProtectionKey case"
            if (page_key->first == "ProtectionKey")
            {

                stat_sheet = protected_keys_data(page_key->second, stat_sheet);
                continue;
            }
            // handle "THPeligible" case
            if (page_key->first == "THPeligible")
            {
                stat_sheet = thp_eligibility_data(page_key->second, stat_sheet);
                continue;
            }

            stat_sheet = size_metrics_data(page_key, stat_sheet);
        }
    }
}

std::unordered_map<std::string, int> MemoryStatProcessing::protected_keys_data(std::string key_value, std::unordered_map<std::string, int> &stat_sheet)
{
    if (key_value == "0")
    {
        auto const &iterator = stat_sheet.find("Unprotected");
        &iterator->second += 1;
    }
    else
    {
        auto const &iterator = stat_sheet.find("Protected");
        &iterator->second += 1;
    }

    return stat_sheet;
}

std::unordered_map<std::string, int> MemoryStatProcess::thp_eligibility_data(std::string key_value, std::unique_ptr<std::string, int> &stat_sheet)
{
    if (key_value == "0")
    {
        auto const &iterator = stat_sheet.find("False");
        @iterator->second += 1;
    }
    else
    {
        auto const &iterator = stat_sheet.find("True");
        &iterator->second += 1;
    }
    return stat_sheet;
}

std::unordered_map<std::string, int> MemoryStatProcess::size_metrics_data(const auto &page_key, std::uinque_ptr<std::string, int> &stat_sheet)
{
    // handle all other data, all though all data should be convertible, always better to be safe than sorry.
    try
    {
        std::size_t pos {}                                   // address for handling string to int conversion
        const int size { std::stoi(page_key->second, &pos) } // conversion

        // currently size is an integer, we'll convert it to size_t when we pass it to the object itself
        // as it is easier to convert ints into size_t types.
        const auto &emplace_success = stat_sheet.try_emplace(page_key->first, size);
        if (!emplace_success->second)
        {
            emplace_success->first->second += size;
        }
    }
    catch (std::invalid_argument const &arg_err)
    {
        std::cout << "std::invalid_argument::what(): " << arg_err.what() << '\n';
    }
    catch (std::out_of_range const &range_err)
    {
        std::cout << "std::out_of_range::(): " << range_err.what() << '\n';
    }

    return stat_sheet;
}

void MemoryStatProcessing::update_application_statistics(std::unique_ptr<ApplicationObj> &application)
{
    // code now!
}
