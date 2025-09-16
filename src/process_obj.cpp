#include "../headers/process_obj.h"

ProcessObj::ProcessObj(std::string pid, std::string name, std::unordered_map<std::string, double> initial)
{
    this->pid = pid;
    this->name = name;
    this->current_statsheet = initial;
}

std::unordered_map<std::string, double> ProcessObj::calculate_update_diff(std::unordered_map<std::string, double> incoming)
{
    std::unordered_map<std::string, double> changes;
    for (auto const &it : incoming)
    {
        auto const &cur_stat = this->current_statsheet.find(it.first);
        if (cur_stat->second == it.second)
        {
            continue;
        }

        double diff = it.second - cur_stat->second;
        changes.emplace(it.first, diff);
        cur_stat->second = it.second;
    }
    return changes;
}
