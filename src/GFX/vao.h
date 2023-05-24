#pragma once

#include "gfx.h"
#include "buffer.h"

class VAO{

    public:
        VAO();
        ~VAO();

        void bind();
        void setAttribute(Buffer &vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

    private:    
        GLuint handle;
};