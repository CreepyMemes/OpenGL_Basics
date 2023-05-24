#include "application.h"

// Application Object Constructor with predefined window size, title and predefined shaders (for now)
Application::Application() : renderer("shader.vs", "shader.fs"){
    renderer.setBuffers();
}

// Loop until the user closes the application
void Application::run(){
    while(!window.shouldClose()){    
        window.processInput();

        renderer.render();

        window.swapBuffers();
        window.pollEvents();
    }
}