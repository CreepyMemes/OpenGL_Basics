#pragma once

#include "window.h"
#include "renderer.h"

class Application{   

    public:
        Application();

        void run();
    
    private:
        Window window;
        Renderer renderer;
};