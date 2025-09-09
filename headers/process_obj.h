#ifndef PROCESS_OBJ_H
#define PROCESS_OBJ_H

#include <unordered_map>
#include <string>

class ProcessObj
{
public:
    /**
     * @brief Constructs "process object" from its PID, name and memory statsheet.
     */
    ProcessObj(std::string pid, std::string name, std::unordered_map<std::string, double> incoming);

    /**
     * @brief checks an incoming process id and checks if it matches the instance's process id.
     * @param pid -> std::string
     * @return bool
     */
    bool process_id_match(std::string pid)
    {
        if (pid == this->pid)
            return true;

        return false;
    }

    /**
     * @brief Checks the difference between the current sheet and the incoming sheet and collects the changes in values
     * in a new map to be passed to the partial updater service in the "application manager" object.
     *
     * @param incoming -> std::unordered_map<std::string, double>
     */
    std::unordered_map<std::string, double> calculate_update_diff(std::unordered_map<std::string, double> incoming);

private:
    std::string pid;
    std::string name;
    std::unordered_map<std::string, double> current_statsheet;
};

#endif // PROCESS_OBJ_H