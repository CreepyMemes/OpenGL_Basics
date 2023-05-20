#include "window.h"

// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Constructor initializes a GLFW window with given size as arguments
Window::Window(int width, int height, const char* title){
    
    // Initialize the GLFW library
    init();

    // Set the OpenGL version and profile
    setWindowHints();

    // Create the GLFW window object
    createWindow(width, height, title);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Callback function on the window that gets called every time the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // Initiate Glad loader
    initGlad();
}

// Destructor method, that destroys the GLFW window object
Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Check if the window should close
bool Window::shouldClose() const {
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

// Swap buffers
void Window::swapBuffers(){
    glfwSwapBuffers(window);
}

//poll IO events (keys pressed/released, mouse moved etc.)
void Window::pollEvents(){
   glfwPollEvents();
}


// --------------------------------------- PRIVATE METHODS ------------------------------------------------

// Attempt to initialize the GLFW library, return -1 if failed
void Window::init(){

    bool success = glfwInit();
    if (success == GLFW_FALSE){
        std::cerr << "[GLFW Error: Failed to initialize GLFW library]" << std::endl;
        assert(success);
    }
}

// Set the major and minor version and profile of OpenGL
void Window::setWindowHints(){

    // Setup hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

// Create the GLFW window object and check for errors
void Window::createWindow(int width, int height, const char* title){

    // Create window Object
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    // Check if it was created successfully
    if (window == NULL){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        assert(window != NULL);
    }
}

// Initialize GLAD by passing the function to load the address of the OpenGL function pointers
void Window::initGlad(){

    // Initialize GLAD Loader and check if it goes successfully
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        assert(false);
    }    
}


// --------------------------------------- OTHER FUNCTIONS ------------------------------------------------

// Callback Function whenever the window size is changed (this callback function executes to update the viewport)
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  