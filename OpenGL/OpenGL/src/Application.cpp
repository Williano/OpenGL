//
//  Application.cpp
//  OpenGL
//
//  Created by William Kpabitey Kwabla on 11/2/19.
//  Copyright © 2019 William Kpabitey Kwabla. All rights reserved.
//

/*
   Standard C++ libraries
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


/*
   Third-party libraries
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

#define ASSERT(x) if(!(x)) __debugbreak();
#define glCall(x) glClearError();\
x;\
ASSERT(glLogCall)

static void glClearError(){
    while (glGetError() != GL_NO_ERROR);
}


static bool glLogCall(){
    while (GLenum error = glGetError()) {
        std::cout<< "[OPENGL Error] (" << error << ")" <<std::endl;
        return false;
    }
    
    return true;
}


struct shaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static shaderProgramSource parseShader(const std::string& filepath){
    
    std::ifstream stream(filepath);
    
    enum class shaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;
    
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = shaderType::VERTEX;
                
            }
            
            else if (line.find("fragment") != std::string::npos) {
                type = shaderType::FRAGMENT;
            }
        }
        else {
            
            ss[(int)type] << line << '\n';
        }
    }
    
    return { ss[0].str(), ss[1].str() };
}

static unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    return id;
}


static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}


int main() {
    
    if(!glfwInit()) {
        std::cout<< "GLFW intialization Failed!" << std::endl;
        return -1;
    }
    
        /* Configure GLFW */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    
    if(!window){
        std::cout<< "Failed to create glfw window" <<std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(1);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout<< "Failed to initialize glew." <<std::endl;
        return -1;
    }
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Vertex data to use for triangle draw
    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };
    
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    // Create a buffer or memory on the VRAM and store your vertex in it.
    //  Create buffer and copy data
    unsigned int buffer; // Stores the ID of the buffer generated
    glGenBuffers(1, &buffer); // Generates a buffer and stores the ID in the buffer variable
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // Select the buffer
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW); // Copy Data in generated Buffer.
    
    
    // define vertex layout
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);
    
    
    // Create an index buffer or memory on the VRAM and store your vertex in it.
    unsigned int ibo; // Stores the ID of the buffer generated
    glGenBuffers(1, &ibo); // Generates a buffer and stores the ID in the buffer variable
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // Select the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW); // Copy Data in generated Buffer.
    
    shaderProgramSource source = parseShader("/Users/william/Documents/Personal/OpenGL/OpenGL/OpenGL/res/shaders/Basic.shader");
    
    unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);
    
    GLint location = glGetUniformLocation(shader, "uColor");
    glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f);
    
    
    float red = 0.0f;
    float step = 0.05f;
    
    while(!glfwWindowShouldClose(window)){
        
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUniform4f(location, red, 0.3f, 0.8f, 1.0f);
        
        // Draw to screen
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
        
        // increment red
        if (red < 0.0f || red > 1.0f)
            step *= -1.0;
        red += step;
        
        
    }
    
    // Cleanup VBO
    glDeleteBuffers(1, &buffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(shader);
    
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}
