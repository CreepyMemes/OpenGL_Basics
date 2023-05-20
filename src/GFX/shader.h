#ifndef SHADER_H
    #define SHADER_H
    
    #include "gfx.h"

    #include <string>
    #include <fstream>
    #include <sstream>
    #include <iostream>
    #include <filesystem>

    #ifdef _WIN32
        #include <io.h>
        #define getExecutablePath(buf, size) _fullpath((buf), _pgmptr, (size))
    #else
        #include <unistd.h>
        #define getExecutablePath(buf, size) readlink("/proc/self/exe", (buf), (size))
    #endif

    // Shader Program Object that reads the shader source files, compiles and links them
    class Shader{

        public:

            // the program's ID
            unsigned int id;

            // Constructor reads and builds the shader
            Shader(char **argv, std::string vertexFileName, std::string fragmentFileName);

            // Use/Activate the shader object
            void use();

            // Utility uniform functions
            void setBool (const std::string &name, bool  value) const;        
            void setInt  (const std::string &name, int   value) const;
            void setFloat(const std::string &name, float value) const;

        private:

            // Return the absolute path of a specified shader's file name (so the App can be run from anywhere)
            std::string getShaderPath(char** argv, const std::string fileName);

            // Open and read the source files of the specified shader's path
            std::string getSource(std::string shaderPath);

            // Compile a shader from source (vertex shader or fragment shader depending on the argument passed)
            unsigned int CompileShader(unsigned int type, const char* source);

            // Create a Program object for by linking the compiled Vertex Shader and Fragment Shader objects
            unsigned int createShader(const unsigned int vertex, const unsigned int fragment);
    };

#endif