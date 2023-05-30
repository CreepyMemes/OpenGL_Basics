#pragma once

#include "opengl.h"
#include "../util/file_handling.h"

#include <iostream>
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

        GLint getUniformLocation(const std::string& name);

        GLuint CompileShader(const GLuint type, const char* source);
        GLuint createShader(const GLuint vertex, const GLuint fragment);
};