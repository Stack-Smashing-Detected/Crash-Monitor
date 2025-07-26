#include "../headers/application_obj.h"
#include <format>

ApplicationObj::ApplicationObj()
{
    // initialize the member variables
    this->spawnedProcesses = 0;
    this->applicationName = "";
    this->protection_level = 0.0;
    this->thp_eligibility = 0.0;
}

void ApplicationObj::update_protection_level(int protected_count, int unprotected_count)
{
    int page_count = protected_count + unprotected_count;
    double protection_value = (static_cast<double>(page_count)/protected_count) * 100;
    this->protection_level = std::format("{}%", protection_value);
}

void ApplicationObj::update_thp_eligibility(int false_count, int true_count)
{
    int page_count = false_count + true_count;
    double thp_eligibility_value = (static_cast<double>(page_count)/true_count) * 100;
    this->thp_eligibility = std::format("{}%", thp_eligibility_value);
}

void ApplicationObj::update_mem_statistic(std::string statistic, size_t amount)
{
    // map the statistic to the statistic_map
    auto const &emplace_success = this->app_mem_statistics.try_emplace(statistic, amount);
    if(!emplace_success.second){
        emplace_success.first->second = amount;
    }
}
