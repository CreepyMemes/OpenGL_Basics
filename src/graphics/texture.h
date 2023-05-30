#pragma once

#include "opengl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/STB/stb_image.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Texture{

    public:
        Texture(const std::string& path);
        ~Texture();

        void bind() const;

    private:
        GLuint handle;

};