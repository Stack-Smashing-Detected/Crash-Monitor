/**
 * @brief Source file for application manager, implements methods defined in application_manager.h
 * @author Victor J Wilson
 */

#include "../headers/application_manager.h"
#include "../headers/memory_stat_processing.h"
#include "../headers/process_algorithms.h"

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

nlohmann::json ApplicationManager::read(int index)
{
    // how do you look up this information.
    using json = nlohmann::json;
    json response;
    if (0 <= index < application_list.size())
    {
        json data;
        auto const &app = this->application_list[index];
        data["Name"] = app->get_application_name();
        data["Size"] = app->get_mem_statistic("Size");
        data["Kernel Page Size"] = app->get_mem_statistic("KernelPageSize");
        data["MMU Page Size"] = app->get_mem_statistic("MMUPageSize");
        data["Rss"] = app->get_mem_statistic("Rss");
        data["Pss"] = app->get_mem_statistic("Pss");
        data["Pss Dirty"] = app->get_mem_statistic("Pss_Dirty");
        data["Shared Clean"] = app->get_mem_statistic("Shared_Clean");
        data["Shared Modified"] = app->get_mem_statistic("Shared_Dirty");
        data["Private Clean"] = app->get_mem_statistic("Private_Clean");
        data["Private Modified"] = app->get_mem_statistic("Private_Dirty");
        data["Referenced Memory"] = app->get_mem_statistic("Referenced");
        data["Anonymous Memory"] = app->get_mem_statistic("Anonymous");
        data["KSM"] = app->get_mem_statistic("KSM");
        data["Lazy Free"] = app->get_mem_statistic("LazyFree");
        data["Anonymous Huge Pages"] = app->get_mem_statistic("AnonHugePages");
        data["Shmem Pmd Mapped"] = app->get_mem_statistic("ShmemPmdMapped");
        data["File Pmd Mapped"] = app->get_mem_statistic("FilePmdMapped");
        data["Shared Huge TLB"] = app->get_mem_statistic("Shared_Hugetlb");
        data["Private Huge TLB"] = app->get_mem_statistic("Private_Hugetlb");
        data["Swap Rss"] = app->get_mem_statistic("Swap");
        data["Swap Pss"] = app->get_mem_statistic("SwapPss");
        data["Locked"] = app->get_mem_statistic("Locked");
        data["Protection Level"] = app->get_current_protection_level();
        data["THP Eligibility"] = app->get_current_thp_eligibility_level();

        response["message"] = "Application data successfully retrieved";
        response["status"] = "SUCCESS";
        response["data"] = data;
        return response;
    }
    else
    {
        response["message"] = "Unable to find application with provided index";
        response["status"] = "FAILURE";
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

void ApplicationManager::initial_create(std::unordered_map<std::string, std::string> applications, MemoryStatProcessing &stat_processor)
{
    for (auto const &it : applications)
    {
        std::unique_ptr<ApplicationObj> app = std::make_unique<ApplicationObj>(it.first, it.second);
        std::string filepath = std::format("../../mem_stats/{}.json", it.first);
        std::unordered_map<std::string, int> stat_sheet = stat_processor.evaluate_memory_stat_sheet(filepath);
        stat_processor.update_application_statistics(app, stat_sheet);
        this->application_list.push_back(app);
    }
}
