#include "GFX/gfx.h"
#include "GFX/window.h"
#include "GFX/renderer.h"

#include <iostream>

int main(){

    // Create our Window Object
    Window window(800, 600, "LearnOpenGL", 3, 3, GLFW_OPENGL_CORE_PROFILE);

    // Create our Renderer Object
    Renderer renderer("shader.vs", "shader.fs");

    // Create an array that contains all the unique vertices that will be loaded into the VBO (vertex buffer)
    float vertices[] = {
        
        // Positions        // Colors
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f    
    };
    
    // Create an array that contains the indices of the vertices that will be loaded into the EBO (face buffer)
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3 
    };      

    // Setup this rendere's Vertex and Element Buffer Objects by loading their data
    renderer.bufferSetup(vertices, sizeof(vertices), indices, sizeof(indices), GL_STATIC_DRAW);
 
    // Loop until the user closes the window
    while(!window.shouldClose()){
       
        // Process input
        window.processInput();

        // Set the color values clear the screen with, and call glClear() to clear it
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.render();
        
        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}

