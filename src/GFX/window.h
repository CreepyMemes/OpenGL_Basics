#ifndef WINDOW_H
    #define WINDOW_H

    #include "gfx.h"
    #include <iostream>
    #include <cassert>

    // Set OpenGL version and profile
    #define OPENGL_VERSION_MAJOR 3
    #define OPENGL_VERSION_MINOR 3
    #define OPENGL_PROFILE GLFW_OPENGL_CORE_PROFILE

    // Window Object Class
    class Window {

        public:

            // Constructor initializes a GLFW window with given size as arguments
            Window(int width, int height, const char* title);

            // Destructor declaration
            ~Window();

            // Check if the window should close
            bool shouldClose() const;

            // Process incoming inputs
            void processInput();
            
            // Swap buffers
            void swapBuffers();

            //poll IO events (keys pressed/released, mouse moved etc.)
            void pollEvents();

        private:

            // GLFW window object 
            GLFWwindow* window;

            // Initialize the GLFW library and check of errors
            void init();

            // Set the window's OpenGL version and profile hints
            void setWindowHints();

            // Create the GLFW window object and check for errors
            void createWindow(int width, int height, const char* title);

            // Initialize GLAD by passing the function to load the address of the OpenGL function pointers
            void initGlad();
    };

    // Whenever the window size is changed (by OS or user resize) this callback function executes to update the values
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
