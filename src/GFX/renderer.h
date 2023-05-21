#ifndef RENDERER_H 
    #define RENDERER_H
    
    #include "gfx.h"
    #include "vao.h"
    #include "buffer.h"
    #include "shader.h"
    #include "error_handling.h"

    class Renderer {

        public:
            Renderer(std::string vertexFileName, std::string fragmentFileName);

            void setBuffers();
            void render();
            void clear();
            void draw();

        private:
            VAO vao; 
            Buffer vbo, ebo;
            Shader shader;
        };

#endif