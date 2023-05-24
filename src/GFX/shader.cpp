#include "shader.h"

// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Constructor reads and builds the shader
Shader::Shader(const std::string& vertexFileName, const std::string& fragmentFileName){

    // Get the shaders absolute path
    std::string vertexPath   = getShaderPath(vertexFileName);
    std::string fragmentPath = getShaderPath(fragmentFileName);

    // Read the source files from their absolute paths
    std::string vertexSource   = getSource(vertexPath);
    std::string fragmentSource = getSource(fragmentPath);

    // Compile the Vertex Shader and Fragment Shader from their sources
    unsigned int vertex   = CompileShader(GL_VERTEX_SHADER,   vertexSource.c_str());
    unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    // Create the Program Object and save it's ID
    handle = createShader(vertex, fragment);
}

// Destructor method, that destroys the Shader Program Object
Shader::~Shader() {
    glDeleteProgram(handle);
}

// Use/Activate the shader object
void Shader::use(){
    glUseProgram(handle);
}

// Utility uniform functions
void Shader::setBool (const std::string& name, bool  value) const{
    glUniform1i(glGetUniformLocation(handle, name.c_str()), (int)value);
}
void Shader::setInt  (const std::string& name, int   value) const{
    glUniform1i(glGetUniformLocation(handle, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const{
    glUniform1f(glGetUniformLocation(handle, name.c_str()), value);
}

// --------------------------------------- PRIVATE METHODS ------------------------------------------------

// Return the absolute path of the shaders, so the App can be run from anywhere
std::string Shader::getShaderPath(const std::string& fileName) {

    // Load the executable's absolute path to the path buffer
    char bufferPath[255] = ""; getExecutablePath(bufferPath, sizeof(bufferPath));

    // Get the executable's path by converting the buffer to an std::string type
    std::string executablePath(bufferPath);

    // Go back one directory level (ignoring the current App executable)
    std::string parentPath = getParentPath(getParentPath(executablePath));
    
    // Construct the shader's file path
    std::string filePath = parentPath + "\\res\\shaders\\" + fileName;
    
    return filePath;
}

// Get the parent path of a given string type path
std::string Shader::getParentPath(const std::string& path) {

    size_t lastSeparator = path.find_last_of('\\');

    if (lastSeparator != std::string::npos) {
        return path.substr(0, lastSeparator);
    }
    return path;
}

// Function that reads the source files
std::string Shader::getSource(const std::string& shaderPath){

    // Ensure ifstream objects can throw exceptions
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    // Variable that will hold the stream
    std::stringstream shaderStream;
    try{
        // Open file with it's path converted to C style string
        shaderFile.open(shaderPath.c_str());
           
        // Read the file's buffer contents into stream
        shaderStream << shaderFile.rdbuf();

        // Close the file handler
        shaderFile.close();
    }
    catch(std::ifstream::failure e){
        std::cerr << "[Shader Error: Failed to read a shader file]" << std::endl;
        abort();
    }

    // Convert stream into string
    return shaderStream.str();
}

// Function to compile a shader (vertex shader or fragment shader depending on the argument passed)
GLuint Shader::CompileShader(const GLuint type, const char* source){
    
    // Creates a shader object and returns it's ID
    GLuint shader = glCreateShader(type);

    // Replaces the source code in a shader object
    glShaderSource(shader, 1, &source, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Error handling message
    int success; glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE){
        int length;           glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char infoLog[length]; glGetShaderInfoLog(shader, length, &length, infoLog);

        std::cerr << "[Shader Error: " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader Failed to compile]\n" << infoLog << std::endl;

        glDeleteShader(shader);
        abort();
    }

    return shader;
}

// Create a Program object for by compiling and linking the Vertex Shader and Fragment Shader sources
GLuint Shader::createShader(const GLuint vertex, const GLuint fragment){
    
    // Creates a program object and returns it's ID
    GLuint program = glCreateProgram();

    // Attach the compiled Vertex Shader Object and Fragment Shader Object to the Program Object and link them
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    // Validate the program
    glValidateProgram(program);

    // Delete the Vertex Shader object and the Fragment shader object because they've been linked to the Program object
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // Return the program's object ID
    return program;
}
