#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "application_obj.h"
#include "process_obj.h"
#include "../nlohmann/json.hpp"
#include <memory>
#include <vector>

/**
 * Forward Delcarations
 */
class ApplicationObj;
class MemoryStatProcessing;

/**
 * @brief A class for managing a list of application processes using a RESTful API design style (minus API Routes).
 * Create, update and delete are all automated which is another key difference with typical APIs as applications are
 * dynamic in nature.
 */

class ApplicationManager
{
public:
    ApplicationManager() {}

    /**
     * @brief check if a name is already registered in the application list if a matching name is found return the index
     * so we can modify the Application Object at that index without
     * @param name -> std::string
     * @return int
     */
    std::optional<size_t> check_if_app_registered(std::string name);

    /**
     * @brief index, passes all important data relating to the application to the view
     * @return std::vector<int>
     */
    nlohmann::json index();

    /**
     * @brief shows a specific application's data with even more details than the index, takes an application name rather than a PID
     * so that we don't expose the application's pid.
     * @param name -> std::string
     * @return Template class (will be a unique pointer to application object).
     */
    nlohmann::json read(std::string name);

    /**
     * @brief creates an application instance if an application initialization signal is recieved.
     * @param pid, name, stat_processor
     */
    nlohmann::json_abi_v3_12_0::json create(std::string pid, std::string name, MemoryStatProcessing &stat_processor);

    /**
     * @brief creates application objects from data generated during application setup.
     * @param applications, stat_processor
     */
    void initial_create(std::unordered_map<std::string, std::string> processes, MemoryStatProcessing &stat_processor);

    /**
     * @brief updates a specific application, again the application is found by name as we don't want to expose its process identifier.
     * @param app_name
     */
    nlohmann::json_abi_v3_12_0::json update_app_obj(std::string name, std::unordered_map<std::string, double> incoming_stats);

    /**
     * @brief destroys the current resource by name, again we don't want to expose the PID of an application for security reasons.
     * unlike typical delete API methods this one does not return the destroyed object.
     * @param name
     * @return
     */
    nlohmann::json_abi_v3_12_0::json delete_app_obj(std::string name);

    /**
    * @brief destroys process owned by app (when a process terminated event is detected)
    * @param name -> std::string
    * @param pid -> std::string
    */
    nlohmann::json_abi_v3_12_0::json delete_process_obj(std::string, std::string name);

private:
    // this will become std::unique_ptr<AppliationList> later
    std::vector<std::unique_ptr<ApplicationObj>> application_list;
};

#endif // APPLICATION_MANAGER_H
