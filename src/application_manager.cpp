/**
 * @brief Source file for application manager, implements methods defined in application_manager.h
 * @author Victor J Wilson
 */

#include "../headers/application_manager.h"
#include "../headers/memory_stat_processing.h"
#include "../headers/process_algorithms.h"

std::optional<size_t> ApplicationManager::check_if_app_registered(std::string name)
{
    auto it = std::find_if(this->application_list.begin(), this->application_list.end(),
                           [&](const std::unique_ptr<ApplicationObj> &app)
                           {
                               return app->match_search(name);
                           });
    if (it != this->application_list.end())
    {
        return std::distance(this->application_list.begin(), it);
    }
    return std::nullopt;
}

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

        // construct json objauto const& emplace_success = application_list.try_emplace()ect
        app_json["Name"] = app->get_application_name();
        app_json["RAM"] = app->get_specific_stat("Pss");
        app_json["Swap"] = app->get_specific_stat("SwapPss");

        // add app_json to "full_data" json_array
        full_data.push_back(app_json);
    }
    return full_data;
}

nlohmann::json ApplicationManager::read(std::string name)
{
    // how do you look up this information.
    using json = nlohmann::json;
    json response;
    if (auto index = check_if_app_registered(name))
    {
        json data;
        auto &app = this->application_list[*index];
    }
    else
    {
        response["message"] = "Unable to find application with provided index";
        response["status"] = "READ FAILURE";
        response["data"] = {};

        return response;
    }
}

nlohmann::json ApplicationManager::create(std::string pid, std::string name, MemoryStatProcessing &stat_processor)
{
    using json = nlohmann::json;

    std::unique_ptr<ApplicationObj> app = std::make_unique<ApplicationObj>(pid, name);
    std::string filepath = std::format("../../mem_stats/{}.json", pid);
    std::unordered_map<std::string, int> stat_sheet = stat_processor.evaluate_memory_stat_sheet(filepath);
    stat_processor.update_application_statistics(app, stat_sheet);
    this->application_list.push_back(app);

    json response;
    json data;
    response["message"] = "Application added to tracking list";
    response["status"] = "SUCCESS";
    data["pid"] = pid;
    data["name"] = name;
    response["data"] = data;
    return response;
}

void ApplicationManager::initial_create(std::unordered_map<std::string, std::string> processes, MemoryStatProcessing &stat_processor)
{
    for (auto const &it : processes)
    {
        std::string filepath = std::format("../../mem_stats/{}.json", it.first);
        std::unordered_map<std::string, int> stat_sheet = stat_processor.evaluate_memory_stat_sheet(filepath);
        std::unique_ptr<ProcessObj> process = std::make_unique<ProcessObj>(it.first, it.second, stat_sheet);

        if (auto index = check_if_app_registered(it.second))
        {
            auto &app = this->application_list[*index];
            app->register_process(std::move(process));
            continue;
        }

        std::unique_ptr<ApplicationObj> app = std::make_unique<ApplicationObj>(it.second);
        this->application_list.push_back(std::move(app));
    }
}

nlohmann::json ApplicationManager::update_app_obj(std::string name, std::unordered_map<std::string, double> incoming_stats)
{
    using json = nlohmann::json;
    json response;

    if (auto index = check_if_app_registered(name))
    {
        json data;
        auto &app = this->application_list[*index];
        app->update_mem_statistics(incoming_stats);
        response["message"] = "Successfully Updated Data";
        response["status"] = "UPDATE SUCCESS";

        for (auto const &it : incoming_stats)
        {
            data[it.first] = app->get_specific_stat(it.first);
        }
        response["updated data"] = data;
        return response;
    }
    else
    {
        response["message"] = "Could not find application with that name";
        response["status"] = "UPDATE FAILURE";
        response["data"] = {};
    }
}

nlohmann::json ApplicationManager::delete_app_obj(std::string name)
{
    using json = nlohmann::json;
    json response;

    auto it = this->application_list.erase(
        std::remove_if(this->application_list.begin(), this->application_list.end(),
                       [&](const std::unique_ptr<ApplicationObj> &app)
                       {
                           return app->match_search(name);
                       }));

    if (it == this->application_list.end())
    {
        response["message"] = "Unable to find application with that name in the tracking list";
        response["status"] = "DELETE FAILURE";
        response["data"] = {};
        return response;
    }

    response["message"] = "Terminated Application was successfully removed from list";
    response["status"] = "DELETE SUCESS";
    response["removed_application"] = name;
    return response;
}
