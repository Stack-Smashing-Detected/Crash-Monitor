#include "../headers/process_algorithms.h"
#include "../nlohmann/json.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <limits>

// error handling
#ifdef _WIN32
#include <windows.h>
#define SYSERROR()  GetLastError()
#else
#include <errno.h>
#define SYSERROR()  errno
#endif

constexpr auto max_size = std::numeric_limits<std::streamsize>::max(); // a global constant that's only used in this application (thus far).

// constructor, sets up the process list and process symlinks for use later.
ProcessAlgorithms::ProcessAlgorithms()
{
    DIR *dir;
    find_processes(dir);
}

void ProcessAlgorithms::find_processes(DIR *dir)
{
    std::vector<std::string> foundProcesses;
    std::vector<std::string> processSymlinks;

    if (!(dir = opendir("/proc")))
    {
        throw std::runtime_error("failed to open process list");
    }

    while (dirent *dirp = readdir(dir))
    {
        // check if it is directory
        if (dirp->d_type != DT_DIR)
            continue;

        // are character names a digit? Processes names are all identified by PIDs.
        if (!std::all_of(dirp->d_name, dirp->d_name + strlen(dirp->d_name),
                         [](char c)
                         { return std::isdigit(c); }))
            continue;

        // convert the c-string into a std::string
        std::string pid(dirp->d_name);
        // filter out the user owned PIDs using std::filesystem::read_symlink()'s error handling. Any PID owned by the system i.e. root will throw an exception via "readlink()"
        // which is implemented in "read_symlink", this exception should be caught as "filesystem::error" which would stop it from being added to our lists.

        try{
            std::stringstream filepathStream;
            filepathStream << "/proc/" << pid << "/exe";
            std::string exePath = filepathStream.str();

            processSymlinks.push_back(std::filesystem::read_symlink(exePath).string());
            foundProcesses.push_back(pid);

        }catch(std::filesystem::filesystem_error fe){
            continue;
        }
    }
    if (closedir(dir))
        throw std::runtime_error(std::strerror(errno));

    // finally set the newly populated data structures so we can use them later.
    this->set_process_list(foundProcesses);
    this->set_symlinks_list(processSymlinks);
}


std::unordered_map<std::string, int> ProcessAlgorithms::get_application_names(std::vector<std::string> processSymlinks)
{
    // a list of application names and occurences of application name i.e the number of processes per application.
    std::unordered_map<std::string, int> appNames;

    for (std::string &symlink : processSymlinks)
    {
        auto const& pos = symlink.find_last_of('/');
        std::string appName = symlink.substr(pos + 1);

        int procCount = 1;
        auto const& result = appNames.try_emplace(appName, procCount);

        if(!result.second){
            result.first->second += 1;
        }
    }

    return appNames;
}


void ProcessAlgorithms::open_smaps(std::vector<std::string> processIndexes){

    // attempt to open the /proc/$$/smaps file
    for (std::string &pid : processIndexes){
        // get filepath to smaps file
        std::string path = std::format("/proc/{}/smaps", pid);
        // open smaps filepath
        std::ifstream smap(path);
        if(smap.is_open()){
            parse_smap(smap, pid); /** FUNCTION CALL ALERT for more details go to line 120 **/
        }else{
            // if this happens then it was probably a zombie process.
            continue;
        }
    }
}

void ProcessAlgorithms::open_smap(std::string pid){
    std::string path = std::format("/proc/{}/smaps", pid);
    std::ifstream smap(path);
    if(smap.is_open()){
        parse_smap(smap, pid);
    }else{
        std::cout << "Error opening file" << std::endl;
    }
}

/**
 * @brief apologies for the double nested while loop but parsing files really is "f**ed" in terms of time complexity.
 * but the bulk of the large time complexity should be spent in setup.
 */
void ProcessAlgorithms::parse_smap(std::ifstream &smap, std::string pid){
    // parse through the smap, we want to find the pss Values since that will identify the exact memory mapping of the process.
    using json = nlohmann::json;
    json process = json::array();

    // a bunch of variables that we'll need for tokenization procedure.
    int index = 0;
    std::string cpp_delim = ": ";
    char *delim = new char[cpp_delim.size() + 1];
    delim[cpp_delim.length()] = '\0';
    std::copy(cpp_delim.begin(), cpp_delim.end(), delim);    // can specify multiple delimiters for more precise tokenization.
    char *saveptr, *token; // saveptr is required for strtok_r
    std::vector<std::string> tokens;
    json page;

    // read each line in proc/pid/smaps until we reach the end.
    while(!smap.eof()){
        // lines with a digit or the letter f (specific to the vsyscall page) indicate a new memory page.
        // we can take an opportunity to build a new json object to add to our json array.
        while(smap.peek() != EOF && !std::isdigit(smap.peek()) && smap.peek() != 'f' ){
            // prepare line for tokenization
            std::string buf;
            std::getline(smap, buf);

            // tokenize line.
            char *buffer = new char[buf.size() + 1];
            buffer[buf.length()] = '\0';
            std::copy(buf.begin(), buf.end(), buffer);
            token = strtok_r(buffer, delim, &saveptr);

            // call strtok_r until it outputs null, should only be 2 times for the most part, last 3 page entries are 1 for 2nd last and 3rd last (THPeligible and ProtectionKey)
            // and an arbitrary number of times for the last entry VmFlags (sometimes a page can have one or 7 different flags).
            while(token != NULL){
                tokens.push_back(token);
                token = strtok_r(nullptr, delim, &saveptr);
            }

            // validate input data using the validateIncomingData helper function,
            // except with the special case for the entry "VmFlags" which is an arbitrary list of virtual memory permissions
            // since VmFlags is the last entry in a memory page we add the page to the process json_array here.
            if(tokens[0] == "VmFlags"){
                if(tokens.size() > 2){
                    std::vector<std::string> flags(tokens.begin() + 1, tokens.end());
                    page[tokens[0]] = flags;
                    process.push_back(page);
                }else{
                    std::vector<std::string> flags;
                    flags.push_back(tokens[1]);
                    page[tokens[0]] = flags;
                    process.push_back(page);
                }
            }else{
                page[tokens[0]] = validate_incoming_data(tokens); /** FUNCION CALL ALERT check line 192 for more details **/
            }
            // free memory allocated to buffer and clear tokens vector.
            delete[] buffer;
            tokens.clear();
        }
        // account for the first line being the descriptor which would mess up the naming convention a little bit.
        if(!process.empty()){
            page.clear();
        }
        // break if peek at EOF
        if(smap.peek() == EOF){
            break;
        }

        // provide the page's indexer (in this case name).
        page["name"] = std::format("mem_page_{}", index);
        // ignore any thing that gets here.
        smap.ignore(max_size, '\n');
        index++;
    }
    // free allocation for delim character
    delete[] delim;

    // finally write the array to the json file.
    std::ofstream out(std::format("../../mem_stats/{}.json", pid));
    if(out.is_open()){
        out << process.dump(4);
    }else{
        std::cerr << "Failed to open file: " << SYSERROR() << std::endl;
    }

}

std::string ProcessAlgorithms::validate_incoming_data(std::vector<std::string> tokens){
    // edge cases.
    if(tokens[0] == "THPeligible" || tokens[0] == "ProtectionKey"){
        return tokens[1];
    }else {
        return std::format("{}{}", tokens[1], tokens[2]);
    }
}
