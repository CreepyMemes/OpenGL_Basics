#pragma once

#include "opengl.h"
#include "../util/path_helper.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Shader{

    public:
        Shader(const std::string& vertexFileName, const std::string& fragmentFileName);
        ~Shader();

        void bind() const;

        void setBool (const std::string& name, bool  value);        
        void setInt  (const std::string& name, int   value);
        void setFloat(const std::string& name, float value);

    private:
        GLuint handle;
        std::unordered_map<std::string, GLint> uniform_location_cache;

        std::string getSource(const std::string& shaderPath);

        GLint getUniformLocation(const std::string& name);

        GLuint CompileShader(const GLuint type, const char* source);
        GLuint createShader(const GLuint vertex, const GLuint fragment);
};