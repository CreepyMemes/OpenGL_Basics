#include "game.h"


Game::Game()
    : window(800, 600, "LearnOpenGL"),
      renderer("shader.vs", "shader.fs") {

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
    renderer.setVBO(vertices, sizeof(vertices),  GL_STATIC_DRAW);
    renderer.setEBO(indices,  sizeof(indices),   GL_STATIC_DRAW);
}

// Main Game Application Loop
void Game::run(){

    // Loop until the user closes the window
    while(!window.shouldClose()){
       
        // Process input
        window.processInput();

        // Clear the screen
        renderer.clear();

        // Draw rendered stuff
        renderer.render();
        
        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.swapBuffers();
        window.pollEvents();
    }

}