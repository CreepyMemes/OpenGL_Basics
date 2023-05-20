#include "renderer.h"

// Initialize VAO VBO EBO and compile Shader 
Renderer::Renderer(std::string vertexFileName, std::string fragmentFileName) 
    : vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER),
      shader(vertexFileName, fragmentFileName) {

        // Nothing to see here ...
}

// Load the VBO and EBO data and configuration
void Renderer::bufferSetup(const void* vertices, size_t verticesSize, const void* indices, size_t indicesSize, GLenum usage){
    
    // Bind the VAO first, so the VBO and EBO configurations get saved
    vao.bind();

    // Load the vertex data to the VBO
    vbo.setData(vertices, verticesSize, usage); 

    // Set the vertex attribute pointers (by their: location, size, type, normalize?, stride, pointer) then enable their "location" with  glEnableVertexAttribArray(location)
    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Load the indices data to the EBO
    ebo.setData(indices, indicesSize, usage);

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