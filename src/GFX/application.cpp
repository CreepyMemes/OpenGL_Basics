#include "application.h"

// Application Object Constructor with predefined window size, title and shaders locations (for now)
Application::Application()
    : renderer("shader.vs", "shader.fs") {

    // Setup this rendere's Vertex and Element Buffer Objects by loading their data
    renderer.setBuffers(); 
}

// Loop until the user closes the window
void Application::run(){
    while(!window.shouldClose()){    
        window.processInput();
        renderer.render();
        window.update();
    }
}