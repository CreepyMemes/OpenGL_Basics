#ifndef VAO_H
    #define VAO_H

    #include "gfx.h"
    
    // Vertex Array Object Class
    class VAO{

        public:

            // Constructor method
            VAO();

            // Destructor method
            ~VAO();

            // Bind the VAO
            void bind();

            // Bind the VAO
            void unbind();

        private:
        
            // The VAO's object ID
            unsigned int id;
    };

#endif