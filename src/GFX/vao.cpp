#include "vao.h"

// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Core OpenGL requires a Vertex Array Object be defined and bound (to store the vertex attribute configurations of the VBOs while it's bound)
VAO::VAO() {
    glGenVertexArrays(1, &id);
}

// Deallocate all the VAO's resources 
VAO::~VAO() {
    glDeleteVertexArrays(1, &id);
}

// bind the VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
void VAO::bind() {
    glBindVertexArray(id);
}

// Unbind the VAO once all VBOs and attrribute configurations are defined (not necessary to do)
void VAO::unbind() {
    glBindVertexArray(0);
}