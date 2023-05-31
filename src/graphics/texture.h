#pragma once

#include "opengl.h"
#include "../util/file_handling.h"

#include <iostream>
#include <string>

class Texture{

    public:
        Texture(const std::string& textureFileName);
        ~Texture();

        void bind() const;

    private:
        GLuint handle;
        GLint width, height, channels;
        unsigned char *image;

        void setParameters() const;

};