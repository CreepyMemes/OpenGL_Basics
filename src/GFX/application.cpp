#include "application.h"

// Application Object Constructor with predefined window size, title and predefined shaders (for now)
Application::Application() : renderer("shader.vs", "shader.fs"){
    
    // Create an array that contains all the unique vertices that will be loaded into the VBO (vertex buffer)
    float vertices[] = {
        
        // Positions        // Colors
         0.2f,  0.2f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.2f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.2f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.2f,  0.2f, 0.0f, 0.0f, 1.0f, 1.0f   
    };
    
    // Create an array that contains the indices of the vertices that will be loaded into the EBO (face buffer)
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3 
    };      

    renderer.set_vbo(vertices, sizeof(vertices));
    renderer.set_ebo(indices,  sizeof(indices));

    for(int i = 0; i < 2; i++) renderer.set_attribute(i, 3, GL_FLOAT, 6 * sizeof(float), i * 3 * sizeof(float));
}

// Loop until the user closes the application
void Application::run(){

    float xoffset=0;
    float yoffset=0;

    float xcount= 0.005;
    float ycount= 0.008;

    while(!window.shouldClose()){    
        window.processInput();

        renderer.set_uniform_float("xoffset", xoffset);
        renderer.set_uniform_float("yoffset", yoffset);

        xoffset += xcount;
        yoffset += ycount;

        if(xoffset >= 0.8 | xoffset <= -0.8) xcount *= -1;
        if(yoffset >= 0.8 | yoffset <= -0.8) ycount *= -1;

        renderer.clear();
        renderer.draw();

        window.swapBuffers();
        window.pollEvents();
    }
}