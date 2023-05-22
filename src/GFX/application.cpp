#include "application.h"

// Application Object Constructor with predefined window size, title and shaders locations (for now)
Application::Application() : window(1200, 720, "OpenGL Template"){
    window.initRenderer("shader.vs", "shader.fs");
    window.setBuffers(); 
}

// Loop until the user closes the window
void Application::run(){
    while(!window.shouldClose()){    
        window.processInput();
        window.render();
        window.update();
    }
}