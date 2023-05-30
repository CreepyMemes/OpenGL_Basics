#include "vao.h"

// Core OpenGL requires a Vertex Array Object be defined and bound (to store the vertex attribute configurations of the VBOs while it's bound)
VAO::VAO() {
    glGenVertexArrays(1, &handle);
}

// Deallocate all the VAO's resources 
VAO::~VAO() {
    glDeleteVertexArrays(1, &handle);
}

// bind the VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
void VAO::bind() {
    glBindVertexArray(handle);
}

// Set a given VBO as argument it's attribute configuration that will get saved in this VAO
void VAO::set_attribute(Buffer &vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset){

    // Bind the VAO and the target VBO
    bind();
    vbo.bind();

    // Note: glVertexAttribPointer() will AUTO-CONVERT integer values to floating point, use glVertexAttribIPointer() for int
    switch (type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:

            glVertexAttribIPointer(index, size, type, stride, (void *) offset);
        break;

        default:
            
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *) offset);
        break;
    }

    glEnableVertexAttribArray(index);
}