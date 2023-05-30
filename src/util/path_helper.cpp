#include "path_helper.h"

// Return the absolute path of the shaders, so the App can be run from anywhere
std::string getFilePath(const std::string& fileName) {

    // Load the executable's absolute path to the path buffer
    char bufferPath[255] = ""; getExecutablePath(bufferPath, sizeof(bufferPath));

    // Get the executable's path by converting the buffer to an std::string type
    std::filesystem::path executablePath(bufferPath);

    // Go back one directory level (ignoring the current App executable)
    std::filesystem::path parentPath = executablePath.parent_path().parent_path();

    // Construct the shader's file path
    std::filesystem::path filePath = parentPath / "res" / "shaders" / fileName;

    return filePath.string();
}
