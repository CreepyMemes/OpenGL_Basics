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

            // Setup the renderer
            void bufferSetup(const void* vertices, size_t verticesSize, const void* indices, size_t indicesSize, GLenum usage);
            
            // Render
            void render();

        private:

            // Vertex Array Object
            VAO vao;

            // Vertex and Element Buffer Objects
            Buffer vbo, ebo;

            // This object's shader
            Shader shader;
        };

#endif