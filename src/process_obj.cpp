#include "../headers/process_obj.h"

ProcessObj::ProcessObj(std::string pid, std::string name, std::unordered_map<std::string, double> initial)
{
    this->pid = pid;
    this->name = name;
    this->current_statsheet = initial;
}

void ProcessObj::do_partial_update(std::unordered_map<std::string, double> incoming_changes)
{
    for (auto const &it : incoming_changes)
    {
        auto const &cur_stat = this->current_statsheet.find(it.first);
        cur_stat->second += it.second;
    }

    this->updated_alert = true;
}
