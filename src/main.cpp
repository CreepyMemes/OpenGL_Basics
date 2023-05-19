#include "gfx/gfx.h"
#include "gfx/shader.h"

#include <iostream>
#include <cassert>

//#define _USE_MATH_DEFINES
//#include <cmath>

// Check if there are errors, if one is found print it then kill the execution with assert
bool glErrorCode();
#define glCheckError() assert(glErrorCode())

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(){
    // // Specify the file path relative to the current working directory
    // std::string filePath = "../res/shaders/shader.vs";

    // // Create an input file stream object and open the file
    // std::ifstream fileStream(filePath);
    
    // // Check if the file was successfully opened
    // if (fileStream.is_open()) {
    //     // Create a string stream object
    //     std::stringstream stringStream;

    //     // Read the file content into the string stream
    //     stringStream << fileStream.rdbuf();

    //     // Close the input file stream
    //     fileStream.close();

    //     // Retrieve the content of the file from the string stream
    //     std::string fileContent = stringStream.str();

    //     // Display the file content
    //     std::cout << fileContent << std::endl;
    // } else {
    //     // Failed to open the file
    //     std::cout << "Failed to open the file." << std::endl;
    // }

    // return 0;







    // Initialize GLFW library
    if (!glfwInit()){
        std::cerr << "Failed to initialize GLFW library" << std::endl;
        return -1;
    }

    // Set the major and minor version both to 3 (OpenGL 3.3), also set GLFW to explicitly use the core-profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Callback function on the window that gets called each time the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // Initialize GLAD by passing the function to load the address of the OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }    

    // Declare our Shader Program Object
    Shader ourShader("../res/shaders/shader.vs", "../res/shaders/shader.fs");

    // Create an array that contains all the unique vertices that will be loaded into the VBO (vertex buffer)
    float vertices[] = {
        
        // Positions        // Colors
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f    
    };
    
    // Create an array that contains the indices of the vertices that will be loaded into the EBO (face buffer)
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3 
    };      

    // Create the variables that will contain the VAO's and VBO's IDs
    unsigned int VAO, VBO, EBO; 
    
    // Core OpenGL requires a Vertex Array Object be defined and bound (to store the vertex attribute configurations of the VBOs while it's bound)
    glGenVertexArrays(1, &VAO); 

    // Generate the Vertex Buffer Object's ID and the Element Buffer Object's ID
    glGenBuffers(1, &VBO); 
    glGenBuffers(1, &EBO); 

    // bind the VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
        
        // Bind the previously created VBO and set it as current GL_ARRAY_BUFFER, then load the "vertices" data to it (in the graphic's card memory)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

        // Set the vertex attribute pointers (by their: location, size, type, normalize?, stride, pointer) then enable their "location" with  glEnableVertexAttribArray(location)
            // Position Attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // Color Attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

        // Bind the previously created EBO and set it as current GL_ELEMENT_ARRAY_BUFFER, then load the "indices" data to it (in the graphic's card memory)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    // Unbind the VAO once all VBOs and attrribute configurations are defined (not necessary to do)
    glBindVertexArray(0); 
    

    // Constants to manipulate the sin values
    //const float multiplier = 4.0f;
    //const float divider = 3.0f;
 
    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window)){
       
        // Process input
        processInput(window);

        // Set the color values clear the screen with, and call glClear() to clear it
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Get current time in seconds since GLFW window has been initialized
        //float timeValue  = glfwGetTime();

        // Set the RGB values with sin wave based on "timeValue"
        //float redValue   = (sin(multiplier * timeValue + M_PI)     + 1.0f) / divider;
        //float greenValue = (sin(multiplier * timeValue)            + 1.0f) / divider;
        //float blueValue  = (sin(multiplier * timeValue + M_PI / 2) + 1.0f) / divider;

        // Get the location of the target uniform
        //int vertexColorLocation = glGetUniformLocation(shaderPrograms[1], "ourColor");

        // Draw rectangles!
        ourShader.use();
        glBindVertexArray(VAO);

        // Change the uniform value every loop (this uniform is used by the shaderProgram in index 1)
        //ourShader.setFloat("someUniform", 1.0f);
        //if== 1) glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

        // Check if there are errors, then print the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glCheckError();
        

        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Deallocate all the resources once the main loop ended
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteProgram(ourShader.id); idk how you would delete the object so i'll leave it commented for now

    // Terminate the GLFW window
    glfwTerminate();
    return 0;
}

// Whenever the window size is changed (by OS or user resize) this callback function executes to update the values
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  

// Process all input, query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window){
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

// Check if there are errors and return False if an error is found, so assert can kill the program
bool glErrorCode() {
    std::string error = "";

    while (GLenum errorCode = glGetError()){
        switch (errorCode){
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            //case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            //case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        }
        std::cerr << "[OPENGL ERROR: " << error << "]" << std::endl;
    }

    return error == "";
}