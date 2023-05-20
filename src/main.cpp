#include "GFX/gfx.h"
#include "GFX/window.h"
#include "GFX/shader.h"
#include "GFX/error_handling.h"

#include <iostream>

//#define _USE_MATH_DEFINES
//#include <cmath>

int main(){

    // Create our Window Object
    Window window(800, 600, "LearnOpenGL", 3, 3, GLFW_OPENGL_CORE_PROFILE);

    // Declare our Shader Program Object with the executable's absolute path
    Shader ourShader("shader.vs", "shader.fs");

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

    // Create the variables that will contain the VAO's and VBO's IDs
    unsigned int VAO, VBO, EBO; 
    
    // Core OpenGL requires a Vertex Array Object be defined and bound (to store the vertex attribute configurations of the VBOs while it's bound)
    glGenVertexArrays(1, &VAO); 

    // Generate the Vertex Buffer Object's ID and the Element Buffer Object's ID
    glGenBuffers(1, &VBO); 
    glGenBuffers(1, &EBO); 

    // bind the VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
        
        // Bind the previously created VBO and set it as current GL_ARRAY_BUFFER, then load the "vertices" data to it (in the graphic's card memory)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

        // Set the vertex attribute pointers (by their: location, size, type, normalize?, stride, pointer) then enable their "location" with  glEnableVertexAttribArray(location)
            // Position Attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // Color Attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

        // Bind the previously created EBO and set it as current GL_ELEMENT_ARRAY_BUFFER, then load the "indices" data to it (in the graphic's card memory)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    // Unbind the VAO once all VBOs and attrribute configurations are defined (not necessary to do)
    glBindVertexArray(0); 
 
    // Loop until the user closes the window
    while(!window.shouldClose()){
       
        // Process input
        window.processInput();

        // Set the color values clear the screen with, and call glClear() to clear it
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw rectangles!
        ourShader.use();
        glBindVertexArray(VAO);

        // Check if there are errors, then print the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glCheckError();
        
        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.swapBuffers();
        window.pollEvents();
    }
    
    // Deallocate all the resources once the main loop ended
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return 0;
}

