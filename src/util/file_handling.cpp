#include "file_handling.h"

// Use of stb functions once and for all
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

// Returns the absolute path of a file inside res folder ( type = "shaders"/"textures"), so the executable App can be run from anywhere
std::string getFilePath(const std::string& fileName, const std::string& type) {

    // Load the executable's absolute path to the path buffer
    char bufferPath[255] = ""; getExecutablePath(bufferPath, sizeof(bufferPath));

    // Get the executable's path by converting the buffer to an std::string type
    std::filesystem::path executablePath(bufferPath);

    // Go back one directory level (ignoring the current App executable)
    std::filesystem::path parentPath = executablePath.parent_path().parent_path();

    // Construct the shader's file path
    std::filesystem::path filePath = parentPath / "res" / type / fileName;

    return filePath.string();
}

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

// Read an image from it's path, and load it's pixel data
unsigned char* readImage(const std::string& path, int& width, int& height, int& channels){

    // OpenGL has texture coordinates with (0, 0) on bottom
    stbi_set_flip_vertically_on_load(true);

    // Read and return the image via the stb library
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    
    // Error handling
    if(image == NULL) {
        std::cerr << "[Texture Error: Failed to read " << std::filesystem::path(path).filename() << "]" << std::endl; 
        abort();
    }

    return image;
}

// Deallocate all resources to the STB image pointer
void freeImage(unsigned char* image){
    stbi_image_free(image);
}