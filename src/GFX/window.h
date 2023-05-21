#ifndef WINDOW_H
    #define WINDOW_H

    #include "gfx.h"
    #include <iostream>

    // Define OpenGL version and profile
    #define OPENGL_VERSION_MAJOR 3
    #define OPENGL_VERSION_MINOR 3
    #define OPENGL_PROFILE GLFW_OPENGL_CORE_PROFILE

    class Window {

        public:
            Window();
            ~Window();

            bool shouldClose();
            void processInput();
            void update();

        private:
            GLFWwindow* window;
            int width = 1280, height = 720;

            void initGlfw();
            void setVersion();
            void createWindow();
            void setupCallbacks();
            void initGlad();

            static void onResized(GLFWwindow* window, int width, int height);
    };
    
#endif
