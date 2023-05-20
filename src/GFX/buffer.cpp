#include "buffer.h"

// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Generate the Buffer Object and set it's type
Buffer::Buffer(GLenum type) {
    glGenBuffers(1, &id);
    this->type = type;
}

// Deallocate all the Buffer's resources 
Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

// Bind the Buffer
void Buffer::bind() {
    glBindBuffer(type, id);
}

// Unbind the Buffer
void Buffer::unbind() {
    glBindBuffer(type, 0);
}

// Bind the Buffer and load data to it (in the graphic's card memory)
void Buffer::setData(const void* data, size_t size, GLenum usage){
    bind();
    glBufferData(type, size, data, usage);
}