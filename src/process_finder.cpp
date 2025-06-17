#include "../headers/process_finder.h"
#include <cstring>

// constructor, sets up the process list.
ProcessFinder::ProcessFinder(DIR *dir) : dir(dir)
{
    std::vector<std::string> processes = ProcessFinder::findProcesses(dir);
}

// default constructor
ProcessFinder::ProcessFinder(){}

std::vector<std::string> ProcessFinder::findProcesses(DIR *dir)
{
    std::vector<std::string> processes;

    if(!(dir = opendir("/proc")))
    {
        throw std::runtime_error("failed to open process list");
    }

    while (dirent *dirp = readdir(dir))
    {
        // check if it is directory
        if(dirp->d_type != DT_DIR)
            continue;

        // are character names a digit? Processes names are all identified by PIDs.
        if(!std::all_of(dirp->d_name, dirp->d_name + strlen(dirp->d_name),
            [](char c){ return std::isdigit(c); }))
                continue;

        // convert the c-string into a std::string
		std::string pid(dirp->d_name);
		processes.push_back(pid);
    }
    if(closedir(dir))
        throw std::runtime_error(std::strerror(errno));

    return processes;
}
