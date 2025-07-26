/**
 * Source file for the Ram Calculator
 *
 * Designed by Victor J Wilson
 * Github: Stack-Smashing-Detected
 **/

#include "../headers/memory_stat_processing.h"
#include "../headers/application_obj.h"
#include "../nlohmann/json.hpp"
#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <unordered_map>

MemoryStatProcessing::MemoryStatProcessing() {} // nothing needs to be setup since data is accessed from file.

void MemoryStatProcessing::evaluate_memory_stat_sheet(std::filesystem::path filepath)
{

    using json = nlohmann::json;
        // read through the json file
    json j_array;
    std::ifstream json_file(filepath.string());

    json_file >> j_array;
    json_file.close();

    std::unordered_map<std::string, int> stat_sheet = get_stat_sheet();
    // prepare unique elements for protection key metric
    int protected_count = 0;
    int unprotected_count = 0;

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
        for (auto page_key = page.begin(); page_key != page.end(); page_key++)
        {
            // handle "ProtectionKey case"
            if (page_key.key() == "ProtectionKey")
            {

                stat_sheet = protected_keys_data(page_key.value(), stat_sheet);
                continue;
            }
            // handle "THPeligible" case
            if (page_key.key() == "THPeligible")
            {
                stat_sheet = thp_eligibility_data(page_key.value(), stat_sheet);
                continue;
            }

            stat_sheet = size_metrics_data(page_key.key(), page_key.value(), stat_sheet);
        }
    }
}

std::unordered_map<std::string, int> MemoryStatProcessing::protected_keys_data(std::string key_value, std::unordered_map<std::string, int> &stat_sheet)
{
    if (key_value == "0")
    {
        auto const &iterator = stat_sheet.find("Unprotected");
        iterator->second += 1;
    }
    else
    {
        auto const &iterator = stat_sheet.find("Protected");
        iterator->second += 1;
    }

    return stat_sheet;
}
std::unordered_map<std::string, int> MemoryStatProcessing::thp_eligibility_data(std::string key_value, std::unordered_map<std::string, int> &stat_sheet)
{
    if (key_value == "0")
    {
        auto const &iterator = stat_sheet.find("False");
        iterator->second += 1;
    }
    else
    {
        auto const &iterator = stat_sheet.find("True");
        iterator->second += 1;
    }
    return stat_sheet;
}

std::unordered_map<std::string, int> MemoryStatProcessing::size_metrics_data(std::string key, std::string key_value,  std::unordered_map<std::string, int> &stat_sheet)
{
    // handle all other data, all though all data should be convertible, always better to be safe than sorry.
    try
    {
        std::size_t pos {};                                   // address for handling string to int conversion
        const int size { std::stoi(key_value, &pos) }; // conversion

        // currently size is an integer, we'll convert it to size_t when we pass it to the object itself
        // as it is easier to convert ints into size_t types.
        auto const &emplace_success = stat_sheet.try_emplace(key, size);
        if (!emplace_success.second)
        {
            emplace_success.first->second += size;
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

void MemoryStatProcessing::update_application_statistics(ApplicationObj &application, std::unordered_map<std::string, int> stat_sheet)
{
    // as these keys are the same for every memory page, we can use a pre-defined array which will look up our map rather than
    // trying to traverse the map using an iterator.
    std::string stat_identifiers[22] = {"AnonHugePages", "Anonymous", "FilePmdMapped", "KSM", "KernelPageSize",
                                        "LazyFree", "Locked", "MMUPageSize", "Private_Clean", "Private_Dirty",
                                        "Private_Hugetlb", "Pss", "Pss_Dirty", "Referenced", "Rss", "Shared_Clean",
                                        "Shared_Dirty", "Shared_Hugetlb", "ShmemPmdMapped", "Size", "Swap", "SwapPss"};

    // check if statsheet is empty
    if(this->stat_sheet.empty()){
        for(std::string statistic : stat_identifiers){
            // find the metric and pass it to the application reference
            auto const &data = stat_sheet.find(statistic);
            application.update_mem_statistic(data->first, data->second);
        }
    }else{
        // we'll design some hashmap comparison with some attempt at caching/memoization to make updates faster.
    }

}
