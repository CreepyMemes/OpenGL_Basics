#pragma once

#include "opengl.h"
#include "vao.h"
#include "buffer.h"
#include "shader.h"
#include "../util/error_handling.h"

class Renderer {

    public:
        Renderer(const std::string& vertexFileName, const std::string& fragmentFileName);

        void set_vbo(const void* data, size_t size);
        void set_ebo(const void* data, size_t size);
        void set_attribute(GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

        void set_uniform_float(const std::string& name, const float value);
        void set_uniform_int  (const std::string& name, const int   value);
        
        void clear();
        void draw();

    private:
        VAO vao; 
        Buffer vbo, ebo;
        Shader shader;
    };