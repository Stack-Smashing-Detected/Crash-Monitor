#include "../headers/utilities.h";
#include <cstdlib>

Utilites::Utilities(std::string *filename){
    // run all utlility functions here
}

Utilities::buildResourcePath(std::string filename){
#if __linux__
#elif _WIN32
#elif __APPLE__
}
