#pragma once

#include "gfx.h"
#include "renderer.h"
#include <iostream>

// Define OpenGL version and profile
#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3
#define OPENGL_PROFILE GLFW_OPENGL_CORE_PROFILE

class Window {

    public:
        Window();
        ~Window();

        void run();

        bool shouldClose();
        void processInput();
        void update();

        void initRenderer(const std::string &vertexFileName, const std::string &fragmentFileName);
        void setBuffers();
        void render();

    private:
        GLFWwindow* window;
        Renderer* renderer;

        const int width = 1200;
        const int height = 720;
        const char* title = "OpenGL Template";

        void initGlfw();
        void setVersion();
        void createWindow();
        void setupCallbacks();
        void initGlad();

        static void onResized(GLFWwindow* window, int width, int height);
};