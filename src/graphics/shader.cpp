#include "shader.h"

// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Constructor reads and builds the shader
Shader::Shader(const std::string& vertexFileName, const std::string& fragmentFileName){

    // Get the shaders absolute path
    std::string vertexPath   = getFilePath(vertexFileName);
    std::string fragmentPath = getFilePath(fragmentFileName);

    // Read the source files from their absolute paths
    std::string vertexSource   = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);

    // Compile the Vertex Shader and Fragment Shader from their sources
    GLuint vertex   = CompileShader(GL_VERTEX_SHADER,   vertexSource.c_str());
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    // Create the Program Object and save it's ID
    handle = createShader(vertex, fragment);
}

// Destructor method, that destroys the Shader Program Object
Shader::~Shader() {
    glDeleteProgram(handle);
}

// Use/Activate the shader object
void Shader::bind() const{
    glUseProgram(handle);
}

// Utility uniform functions
void Shader::setBool (const std::string& name, bool  value){
    glUniform1i(getUniformLocation(name), (int)value);
}
void Shader::setInt  (const std::string& name, int   value){
    glUniform1i(getUniformLocation(name), value);
}
void Shader::setFloat(const std::string& name, float value){
    glUniform1f(getUniformLocation(name), value);
}

// Checks if the location of a given uniform is already saved in the unordered map, if not then gets it's location and checks if it's valid then saves it in cache
GLint Shader::getUniformLocation(const std::string& name){

    if(uniform_location_cache.find(name) != uniform_location_cache.end())
        return uniform_location_cache[name];

    GLint location = glGetUniformLocation(handle, name.c_str());

    if(location == -1){
        std::cerr<<"[Shader Error: uniform '" << name << "' not found in shader]\n";
        abort();
    }
    
    uniform_location_cache[name] = location;
    
    return location;
}

// --------------------------------------- PRIVATE METHODS ------------------------------------------------

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
