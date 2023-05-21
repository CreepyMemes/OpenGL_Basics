#include "buffer.h"

// Generate the Buffer Object and set it's type
Buffer::Buffer(GLint type, bool dynamic) : type(type), dynamic(dynamic){
    glGenBuffers(1, &handle);
}

// Deallocate all the Buffer's resources 
Buffer::~Buffer() {
    glDeleteBuffers(1, &handle);
}

// Bind the Buffer
void Buffer::bind() {
    glBindBuffer(type, handle);
}

// Bind the Buffer and load data to it (in the graphic's card memory)
void Buffer::setData(const void* data, size_t size){
    bind();
    glBufferData(type, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}