#pragma once

#include "opengl.h"

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