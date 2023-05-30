#pragma once

#include "opengl.h"

class Buffer{

    public:
        Buffer(GLint type, bool dynamic);
        ~Buffer();

        void bind();
        void setData(const void* data, size_t size);

    private:
        GLuint handle;
        GLint type;
        bool dynamic;
};

