#include "GFX/gfx.h"
#include "GFX/window.h"
#include "GFX/shader.h"
#include "GFX/vao.h"
#include "GFX/buffer.h"
#include "GFX/error_handling.h"

#include <iostream>

int main(){

    // Create our Window Object
    Window window(800, 600, "LearnOpenGL", 3, 3, GLFW_OPENGL_CORE_PROFILE);

    // Create our Shader Program Object with the executable's absolute path
    Shader ourShader("shader.vs", "shader.fs");

    // Create a Vertex Array Object
    VAO vao;

    // Create a Vertex Buffer Object and an Element Buffer Object
    Buffer vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER);

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

    // bind the VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    vao.bind();
        
        // Load vertices data to the VBO
        vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);

        // Set the vertex attribute pointers (by their: location, size, type, normalize?, stride, pointer) then enable their "location" with  glEnableVertexAttribArray(location)
        // Position Attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Color Attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Load the indices data to the EBO 
        ebo.setData(indices, sizeof(indices), GL_STATIC_DRAW);

    // Unbind the VAO once all VBOs and attrribute configurations are defined (not necessary to do)
    vao.unbind();
 
    // Loop until the user closes the window
    while(!window.shouldClose()){
       
        // Process input
        window.processInput();

        // Set the color values clear the screen with, and call glClear() to clear it
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw rectangles!
        ourShader.use();
        vao.bind();

        // Check if there are errors, then print the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glCheckError();
        
        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}

