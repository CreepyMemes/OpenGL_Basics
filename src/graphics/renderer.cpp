#include "renderer.h"

// Initialize VAO VBO EBO and compile Shader from given shader's file names
Renderer::Renderer(const std::string& vertexFileName, const std::string& fragmentFileName) 
    : vbo(GL_ARRAY_BUFFER, false), 
      ebo(GL_ELEMENT_ARRAY_BUFFER, false),
      shader(vertexFileName, fragmentFileName) {}

// Load vertices data to the VBO
void Renderer::set_vbo(const void* data, size_t size){
    vao.bind();
    vbo.setData(data, size); 
}

// Load indices data to the EBO
void Renderer::set_ebo(const void* data, size_t size){
    vao.bind();
    ebo.setData(data, size);   
}

// Set attribute configuration to the VBO
void Renderer::set_attribute(GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset){
    vao.bind();
    vao.set_attribute(vbo, index, size, type, stride, offset);  
}

// Load float value to the defined shader's uniform given by it's name
void Renderer::set_uniform_float(const std::string& name, const float value){
    shader.bind();
    shader.setFloat(name, value);
}

// Load float value to the defined shader's uniform given by it's name
void Renderer::set_uniform_int(const std::string& name, const int value){
    shader.bind();
    shader.setInt(name, value);
}

// Clear the screen and check for errors
void Renderer::clear(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glCheckError();
}

// Draw elements and check if there are errors
void Renderer::draw(){
    vao.bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glCheckError();
}