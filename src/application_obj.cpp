#include "../headers/application_obj.h"
#include <format>

ApplicationObj::ApplicationObj(std::string name)
{
    this->application_name = name;
}

void ApplicationObj::register_process(std::unique_ptr<ProcessObj> discovered_process)
{
    this->owned_processes.push_back(std::move(discovered_process));
}

int ApplicationObj::get_mem_statistic(std::string statistic)
{
    auto const &target_stat = this->app_mem_statistics.find(statistic);
    if (target_stat == this->app_mem_statistics.end())
        return -1;

    return target_stat->second;
}

void ApplicationObj::update_mem_statistics(std::unordered_map<std::string, double> stat_changes)
{
    // map the statistic to the statistic_map
    for (auto const &it : stat_changes)
    {
        auto const &insert_success = this->app_mem_statistics.try_emplace(it.first, it.second);
        // if the item exists, update the value of that item with the new item value.
        if (!insert_success.second)
        {
            insert_success.first->second += it.second;
        }
    }
}
