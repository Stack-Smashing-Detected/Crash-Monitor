#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <filesystem>

class Utilities {
private:
    std::string filepath;

public:
    // constructor
    Utilities(String* filename);
    // destructor
    ~Utilities();

    // create a filepath for a resource e.g. image if needed.
    std::string buildResourcePath(std::string filename);

    std::string getfilepath(){
        return this->filepath;
    }

};

#endif // UTILITIES_H
