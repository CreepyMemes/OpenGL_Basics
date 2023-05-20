#include "renderer.h"

// Initialize VAO VBO EBO and compile Shader 
Renderer::Renderer(std::string vertexFileName, std::string fragmentFileName) 
    : vbo(GL_ARRAY_BUFFER), 
      ebo(GL_ELEMENT_ARRAY_BUFFER),
      shader(vertexFileName, fragmentFileName) {}

// Load the VBO data and configuration
void Renderer::setVBO(const void* vertices, size_t size, GLenum usage){
    
    // Bind the VAO first, so the VBO configurations get saved
    vao.bind();

    // Load the vertex data to the VBO
    vbo.setData(vertices, size, usage); 

    // Set the vertex attribute pointers (by their: location, size, type, normalize?, stride, pointer) then enable their "location" with  glEnableVertexAttribArray(location)
    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO once all VBOs and attrribute configurations are defined (not necessary to do)
    vao.unbind();
}

// Load the EBO data and configuration
void Renderer::setEBO(const void* indices, size_t size, GLenum usage){
    
    // Bind the VAO first, so EBO configurations get saved
    vao.bind();
    
    // Load the indices data to the EBO
    ebo.setData(indices, size, usage);

    // Unbind the VAO once all VBOs and attrribute configurations are defined (not necessary to do)
    vao.unbind();
}

// Draw things with previously configured VAO and it's VBO/EBO data
void Renderer::render() {

    // Bind the VAO, so the previously saved configurations get loaded
    vao.bind();

    // Use the selected shader compiled when this object was initialized
    shader.use();

    // Draw elements and check if there are errors
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glCheckError();

    // Unbind the vao after we used it (again it's not necessary to do...)
    vao.unbind();
}

// Clear the screen
void Renderer::clear(){

    // Set the color values clear the screen with, and call glClear() to clear it
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}