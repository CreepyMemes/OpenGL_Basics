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

        private:
            VAO vao; 
            Buffer vbo, ebo;
            Shader shader;

            float xoffset=0;
            float yoffset=0;

            float xcount= 0.005;
            float ycount= 0.008;
            
            void clear();
            void draw();

        };

#endif