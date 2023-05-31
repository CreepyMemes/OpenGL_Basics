#include "texture.h"

// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Constructor reads and generates a texture from it's file name
Texture::Texture(const std::string& textureFileName){

    // Generate the texture buffer and assign it's ID
    glGenTextures(1, &handle);
    
    // Bind this texture
    bind();

    // Set this texture's parameters
    setParameters();

    // Get the texture's absolute path
    std::string texturePath = getFilePath(textureFileName, "images");

    // Read the texture's image file from it's absolute path and load it's pixels data
    image = readImage(texturePath, width, height, channels);

    // Load all the texture's pixel data to OpenGL's buffer memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Deallocate the resources for the previously created image pointer
    freeImage(image);
}

// Deallocate all the Textures's resources 
Texture::~Texture(){
    glDeleteTextures(1, &handle);
}

// Bind the Texture
void Texture::bind() const{
    glBindTexture(GL_TEXTURE_2D, handle);
}


// --------------------------------------- PRIVATE METHODS ------------------------------------------------

// Sets some default parameters for the defined texture
void Texture::setParameters() const{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}