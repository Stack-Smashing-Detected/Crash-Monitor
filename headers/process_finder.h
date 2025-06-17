#ifndef PROCESS_FINDER_H
#define PROCESS_FINDER_H

#include <algorithm>
#include <stdexcept>
#include <cerrno>
#include <memory>
#include <vector>
#include <string>
#include <dirent.h>

class ProcessFinder {

public:
    ProcessFinder(DIR *dir); // setup directory
    ProcessFinder();

    // get all the process names we'll need this to access the process data
	// for displaying ram usage, cpu usage, application logos for UI enhancement etc.
    std::vector<std::string> findProcesses(DIR *dir);

    // get the list of process pid's to use throughout the app
    std::vector<std::string> getProcessList(){
        return processes;
    }

private:
    DIR *dir;
    std::vector<std::string> processes;
};

#endif // PROCESS_FINDER_H
