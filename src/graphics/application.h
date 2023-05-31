#pragma once

#include "window.h"
#include "renderer.h"
#include "texture.h"

class Application{   

    public:
        Application();

        void run();
    
    private:
        Window window;
        Renderer renderer;
        Texture texture;
};