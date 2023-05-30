#pragma once

#include "opengl.h"
#include "buffer.h"

class VAO{

    public:
        VAO();
        ~VAO();

        void bind();
        void set_attribute(Buffer &vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

    private:    
        GLuint handle;
};