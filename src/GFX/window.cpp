#include "window.h"

// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Constructor initializes a GLFW window with given size as arguments
Window::Window(){
    
    initGlfw();
    setVersion();
    createWindow();
    glfwMakeContextCurrent(window);
    initGlad();
    setupCallbacks();
}

// Destructor method, that destroys the GLFW window object
Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Check if the window should close
bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

// Process incoming inputs
void Window::processInput(){

    // Close window if ESC is clicked
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // Draw in wireframe polygons if W is clicked
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // Switch off Wireframe mode if Q is clicked
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

// Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
void Window::update(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}


// --------------------------------------- PRIVATE METHODS ------------------------------------------------

// Attempt to initialize the GLFW library, return -1 if failed
void Window::initGlfw(){

    bool success = glfwInit();
    if (success == GLFW_FALSE){
        std::cerr << "[GLFW Error: Failed to initialize GLFW library]" << std::endl;
        abort();
    }
}

// Set the major and minor version and profile of OpenGL
void Window::setVersion(){

    // Setup hints
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

// Create the GLFW window object and check for errors
void Window::createWindow(){

    // Create window Object
    window = glfwCreateWindow(width, height, "OpenGL Template", NULL, NULL);

    // Check if it was created successfully
    if (window == NULL){
        std::cerr << "[GLFW Error: Failed to create GLFW window]" << std::endl;
        abort();
    }
}

// Setup all the call back functions
void Window::setupCallbacks(){

    // Callback function when the window gets resized
    glfwSetFramebufferSizeCallback(window, onResized);  
}

// Initialize GLAD by passing the function to load the address of the OpenGL function pointers
void Window::initGlad(){

    // Initialize GLAD Loader and check if it goes successfully
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "[GLAD Error: Failed to initialize GLAD loader]" << std::endl;
        abort();
    }    
}

// Callback Function whenever the window size is changed (this callback function executes to update the viewport)
void Window::onResized(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  