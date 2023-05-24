#include "renderer.h"


// --------------------------------------- PUBLIC METHODS ------------------------------------------------

// Initialize VAO VBO EBO and compile Shader from given shader's file names
Renderer::Renderer(const std::string& vertexFileName, const std::string& fragmentFileName) 
    : vbo(GL_ARRAY_BUFFER, false), 
      ebo(GL_ELEMENT_ARRAY_BUFFER, false),
      shader(vertexFileName, fragmentFileName) {}

// Load the VBO data and configuration
void Renderer::setBuffers(){

    // Create an array that contains all the unique vertices that will be loaded into the VBO (vertex buffer)
    float vertices[] = {
        
        // Positions        // Colors
         0.2f,  0.2f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.2f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.2f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.2f,  0.2f, 0.0f, 0.0f, 1.0f, 1.0f   
    };
    
    // Create an array that contains the indices of the vertices that will be loaded into the EBO (face buffer)
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3 
    };      

    vao.bind();

    vbo.setData(vertices, sizeof(vertices)); 
    ebo.setData(indices,  sizeof(indices));

    // Set Postion and Color Attributes (note this only works if all attributes are GL_FLOAT and have 3 elements)
    for(int i = 0; i < 2; i++) vao.setAttribute(vbo, i, 3, GL_FLOAT, 6 * sizeof(float), i * 3 * sizeof(float));
}

// Draw things with previously configured VAO and it's VBO/EBO data and us the shader
void Renderer::render() {
    vao.bind();
    shader.bind();

    shader.setFloat("xoffset", xoffset);
    shader.setFloat("yoffset", yoffset);

    xoffset += xcount;
    yoffset += ycount;

    if(xoffset >= 0.8 | xoffset <= -0.8) xcount *= -1;
    if(yoffset >= 0.8 | yoffset <= -0.8) ycount *= -1;

    clear();
    draw();
}


// --------------------------------------- PRIVATE METHODS ------------------------------------------------

// Clear the screen and check for errors
void Renderer::clear(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glCheckError();
}

// Draw elements and check if there are errors
void Renderer::draw(){
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glCheckError();
}


// --------------------------------------- OTHER FUNCTIONS ------------------------------------------------

// Check if there are errors and return False if an error is found (so assert can kill the program)
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
        std::cerr << "[OpenGL Error: " << error << "]\n";
    }

    return error == "";
}