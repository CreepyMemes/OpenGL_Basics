#ifndef RENDERER_H 
    #define RENDERER_H
    
    #include "gfx.h"
    #include "vao.h"
    #include "buffer.h"
    #include "shader.h"
    #include "error_handling.h"

    // Renderer Object Class
    class Renderer {

        public:

            // Constructor method
            Renderer(std::string vertexFileName, std::string fragmentFileName);

            // Setup the VBO and EBO data/configurations 
            void setVBO(const void* vertices, size_t verticesSize,GLenum usage);
            void setEBO(const void* indices,  size_t indicesSize, GLenum usage);
            
            // Draw stuff with VAO configuration
            void render();

            // Clear the screen
            void clear();

        private:

            // Vertex Array Object
            VAO vao;

            // Vertex and Element Buffer Objects
            Buffer vbo, ebo;

            // This object's shader
            Shader shader;
        };

#endif