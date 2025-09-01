#include "application_obj.h"
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
     * @brief index, passes all important data relating to the application to the view
     * @return std::vector<int>
     */
    nlohmann::json index();

    /**
     * @brief shows a specific application's data with even more details than the index, takes an application name rather than a PID
     * so that we don't expose the application's pid.
     * @param name
     * @return Template class (will be a unique pointer to application object).
     */
    nlohmann::json read(int index);

    /**
     * @brief creates an application instance if an application initialization signal is recieved.
     * @param pid, name, stat_processor
     */
    nlohmann::json create(std::string pid, std::string name, MemoryStatProcessing &stat_processor);

    /**
     * @brief creates application objects from data generated during application setup.
     * @param applications, stat_processor
     */
    void initial_create(std::unordered_map<std::string, std::string> applications, MemoryStatProcessing &stat_processor);

    /**
     * @brief updates a specific application, again the application is found by name as we don't want to expose its process identifier.
     * @param app_name
     */
    nlohmann::json update(std::string app_name);

    /**
     * @brief destroys the current resource by name, again we don't want to expose the PID of an application for security reasons.
     * unlike typical delete API methods this one does not return the destroyed object.
     * @param name
     * @return
     */
    nlohmann::json destroy(std::string name);

private:
    // this will become std::unique_ptr<AppliationList> later
    std::vector<std::unique_ptr<ApplicationObj>> application_list;
};
