#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cassert>

static unsigned int CompileShader(unsigned int type, const std::string& source);
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

#define glCall(x) glClearError(); x; assert(glLogCall())
static void glClearError();
static bool glLogCall();
static std::string get_error_code(const GLenum errorCode);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Define the vertex shader source
std::string vertexShader = 
    "#version 330 core\n"
    "\n"
    "layout (location = 0) in vec3 aPos;\n"
    "\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

// Define the fragment shader source
std::string fragmentShaders[2] = { 
    "#version 330 core\n"
    "\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main(){\n"
    "   FragColor = vec4(1.1f, 0.5f, 0.0f, 1.0f);\n"
    "}\n",

    "#version 330 core\n"
    "\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main(){\n"
    "   FragColor = vec4(0.0f, 0.5f, 1.0f, 1.0f);\n"
    "}\n"
};

int main(){

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

    // Pass GLAD the function to load the address of the OpenGL function pointers which is OS-specific
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }    

    // Create the shader program and set it as the current active shader program (with glUseProgram)
    unsigned int shaderPrograms[2];

    for (int i = 0; i < 2; i++) {
        shaderPrograms[i] = CreateShader(vertexShader, fragmentShaders[i]);    
    }

    
    // Create an array that contains all the unique vertices that will be loaded into the VBO (vertex buffer)
    float vertices[2][12] = {
        {
             0.1f,  0.1f, 0.0f,
             0.1f, -0.9f, 0.0f,
            -0.9f, -0.9f, 0.0f,
            -0.9f,  0.1f, 0.0f 
        }, 
        {
             0.9f,  0.9f, 0.0f,
             0.9f, -0.1f, 0.0f,
            -0.1f, -0.1f, 0.0f,
            -0.1f,  0.9f, 0.0f 
        }
    };
    
    // Create an array that contains the indices of the vertices that will be loaded into the EBO (face buffer)
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3 
    };      

    // Create the variables that will contain the VAO's and VBO's IDs
    unsigned int VAOs[2], VBOs[2], EBOs[2]; 
    
    for(int i = 0; i < 2; i++){

        // Core OpenGL requires a Vertex Array Object be defined and bound (to store the vertex attribute configurations of the VBOs while it's bound)
        glGenVertexArrays(1, &VAOs[i]); 

        // Generate the Vertex Buffer Object's ID and the Element Buffer Object's ID
        glGenBuffers(1, &VBOs[i]); 
        glGenBuffers(1, &EBOs[i]); 

        // bind the VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAOs[i]);
            
            // Bind the previously created VBO and set it as current GL_ARRAY_BUFFER, then load the "vertices" data to it (in the graphic's card memory)
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW); 

            // Set the vertex attribute pointers (by their: index, size, type, normalize?, stride, pointer) then enable it
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // Bind the previously created EBO and set it as current GL_ELEMENT_ARRAY_BUFFER, then load the "indices" data to it (in the graphic's card memory)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

            
        // Unbind the VAO once all VBOs and attrribute configurations are defined (not necessary to do)
        glBindVertexArray(0); 
    }

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window)){
       
        // Process input
        processInput(window);

        // Set the color values clear the screen with, and call glClear() to clear it
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

            // Draw rectangles!
            for(int i = 0; i < 2; i++){
                glUseProgram(shaderPrograms[i]);
                glBindVertexArray(VAOs[i]);

                // Check if there are errors, then print the triangle
                glCall( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0) );
            }

        // Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Deallocate all the resources once the main loop ended
    for(int i = 0; i < 2; i++){
        glDeleteVertexArrays(1, &VAOs[i]);
        glDeleteBuffers(1, &VBOs[i]);
        glDeleteBuffers(1, &EBOs[i]);
        glDeleteProgram(shaderPrograms[i]);
    }

    // Terminate the GLFW window
    glfwTerminate();
    return 0;
}

static void glClearError(){
    while (glGetError() != GL_NO_ERROR);
}

static std::string get_error_code(const GLenum errorCode){
    switch (errorCode){
        case GL_INVALID_ENUM:                  return "INVALID_ENUM";
        case GL_INVALID_VALUE:                 return "INVALID_VALUE";
        case GL_INVALID_OPERATION:             return "INVALID_OPERATION";
        //case GL_STACK_OVERFLOW:                return "STACK_OVERFLOW";
        //case GL_STACK_UNDERFLOW:               return "STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:                 return "OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION";
        default: return "UKNOWN_ERROR";
    }
}

static bool glLogCall(){
    while(GLenum error = glGetError()){
        std::cerr << "[OpenGL Error] (" << get_error_code(error) << ") -> ";
        return false;
    }
    return true;
}

// Create a Program object for by compiling and linking the Vertex Shader and Fragment Shader sources
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    
    // Compile the Vertex Shader and the Fragment Shader
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // Creates a program object and returns it's ID
    unsigned int program = glCreateProgram();

    // Attach compiled Vertex Shader and Fragment shader to the Program object and link it, then validate it
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Delete the Vertex Shader object and the Fragment shader object because they've been linked to the Program object
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

// Function to compile a shader (vertex shader or fragment shader depending on the argument passed)
static unsigned int CompileShader(unsigned int type, const std::string& source){
    
    // Creates a shader object and returns it's ID
    unsigned int id = glCreateShader(type);

    // Convert source string to a raw C string (so it can be accepted by glShaderSource())
    const char* src = source.c_str();

    // Replaces the source code in a shader object
    glShaderSource(id, 1, &src, NULL);

    // Compile the shader
    glCompileShader(id);

    // Error handling message
    int success; glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE){
        int length;           glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char infoLog[length]; glGetShaderInfoLog(id, length, &length, infoLog);

        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n" << infoLog << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
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