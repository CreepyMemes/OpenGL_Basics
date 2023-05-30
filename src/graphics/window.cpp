#include "window.h"

// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Constructor initializes a GLFW window with given size as arguments
Window::Window(){   
    init_glfw();
    setVersion();
    createWindow();
    glfwMakeContextCurrent(window);
    init_glad();
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

// Swap frond and back buffers
void Window::swapBuffers(){
    glfwSwapBuffers(window);
}

// Poll IO events (keys pressed/released, mouse moved etc.)
void Window::pollEvents(){
    glfwPollEvents();
}


// --------------------------------------- PRIVATE METHODS ------------------------------------------------

// Attempt to initialize the GLFW library, return -1 if failed
void Window::init_glfw(){
    bool success = glfwInit();

    if (success == GLFW_FALSE){
        std::cerr << "[GLFW Error: Failed to initialize GLFW library]" << std::endl;
        abort();
    }
}

// Set the major and minor version and profile of OpenGL
void Window::setVersion(){
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
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL){
        std::cerr << "[GLFW Error: Failed to create GLFW window]" << std::endl;
        abort();
    }
}

// Setup all the call back functions
void Window::setupCallbacks(){
    glfwSetFramebufferSizeCallback(window, resize_callback);  
}

// Initialize GLAD by passing the function to load the address of the OpenGL function pointers
void Window::init_glad(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "[GLAD Error: Failed to initialize GLAD loader]" << std::endl;
        abort();
    }    
}

// Callback Function whenever the window size is changed (this callback function executes to update the viewport)
void Window::resize_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  