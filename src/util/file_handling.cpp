#include "file_handling.h"

// Function that reads the the contents of a text file
std::string readFile(const std::string& path){

    // Ensure ifstream objects can throw exceptions
    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    // Variable that will hold the stream
    std::stringstream stream;
    try{
        // Open file with it's path converted to C style string
        file.open(path.c_str());
           
        // Read the file's buffer contents into stream
        stream << file.rdbuf();

        // Close the file handler
        file.close();
    }
    catch(std::ifstream::failure e){
        std::cerr << "[File Error: Failed to read " << std::filesystem::path(path).filename() << "]" << std::endl;
        abort();
    }

    // Convert stream into string
    return stream.str();
}