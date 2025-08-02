/**
 * @brief Source file for application manager, implements methods defined in application_manager.h
 * @author Victor J Wilson
 */

#include "../headers/application_manager.h"
#include "../headers/memory_stat_processing.h"

/** this just needs to return the proportional set size in both RAM and in swap memory
 * as well as the name of the application those are the most important metrics.
 * In the future for improved user experience it will also pass the logo.
 */
nlohmann::json ApplicationManager::index()
{
    using json = nlohmann::json;

    // the array of json objects representing the typical API response for an index/browse route.
    json full_data;

    for (auto const &app : this->application_list)
    {
        json app_json; // initialize single json object represting app data we want to send

        // construct json object
        app_json["Name"] = app->get_application_name();
        app_json["RAM"] = app->get_mem_statistic("Pss");
        app_json["Swap"] = app->get_mem_statistic("SwapPss");

        // add app_json to "full_data" json_array
        full_data.push_back(app_json);
    }
    return full_data;
}

nlohmann::json ApplicationManager::read(std::string pid)
{
    // how do you look up this information.
    using json = nlohmann::json;
    json placeholder;
    placeholder["PID"] = pid;

    return placeholder;
}

void ApplicationManager::create(std::string pid)
{
    // What do you need?
}

void ApplicationManager::initial_create(std::unordered_map<std::string, std::string> applications, MemoryStatProcessing &stat_processor)
{
    for (auto const &it : applications)
    {
        // get application name
        size_t pos = it.second.find_last_of('/');
        std::string name = it.second.substr(pos + 1);

        std::unique_ptr<ApplicationObj> app = std::make_unique<ApplicationObj>(it.first, name);
        // prepare the json_file for parsing into our stat_sheet
        std::string filepath = std::format("../../mem_stats/{}.json", it.first);
        // get the latest stat_sheet
        std::unordered_map<std::string, int> stat_sheet = stat_processor.evaluate_memory_stat_sheet(filepath);
        // update the application's statistics
        stat_processor.update_application_statistics(app, stat_sheet);
    }
}
