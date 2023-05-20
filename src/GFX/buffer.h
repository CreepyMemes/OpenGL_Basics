#ifndef BUFFER_H
    #define BUFFER_H

    #include "gfx.h"
    
    class Buffer{

        public:
            // Constructor method
            Buffer(GLenum type);

            // Destructor method
            ~Buffer();

            // Bind the VBO
            void bind();

            // Bind the VBO
            void unbind();

            // Set the VBO's data configuration
            void setData(const void* data, size_t size, GLenum usage);

        private:

            // The VAO's object ID
            unsigned int id;
            GLenum type;
    };

#endif