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
    ProcessObj(std::string pid, std::string name, std::unordered_map<std::string, double> initial);

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
     * @brief returns a reference to the process' current statsheet
     * @return
     */
    std::unordered_map<std::string, double>& get_process_statsheet_ref(){
        return this->current_statsheet;
    }

    /**
     * @brief recieves a map of changed statistics from last snapshot and updates the matching changed statistics.
     * @param incoming -> std::unordered_map<std::string, double>
     * @return void
     */
    void do_partial_update(std::unordered_map<std::string, double> incoming);

    /**
     * @brief replace old statsheet with new statsheet
     * @return void
     */
    void update_process_statsheet(std::unordered_map<std::string, double> incoming){
        this->current_statsheet = incoming;
    }

private:
    bool updated_alert = false;
    std::string pid;
    std::string name;
    std::unordered_map<std::string, double> current_statsheet;
};

#endif // PROCESS_OBJ_H
