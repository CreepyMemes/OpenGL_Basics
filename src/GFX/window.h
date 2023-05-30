#pragma once

#include "opengl.h"
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
        void swapBuffers();
        void pollEvents();

    private:
        GLFWwindow* window;

        const int width = 1200;
        const int height = 720;
        const char* title = "OpenGL Template";
        
        void init_glfw();
        void setVersion();
        void createWindow();
        void setupCallbacks();
        void init_glad();

        static void resize_callback(GLFWwindow* window, int width, int height);
};