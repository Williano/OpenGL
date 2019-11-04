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


/*
   Third-party libraries
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC


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
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout<< "Failed to initialize glew." <<std::endl;
        return -1;
    }
    
    // Vertex data to use for triangle draw
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };
    
    
    // Create a buffer or memory on the VRAM and store your vertex in it.
    unsigned int buffer; // Stores the ID of the buffer generated
    glGenBuffers(1, &buffer); // Generates a buffer and stores the ID in the buffer variable
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // Select the buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // Copy Data in generated Buffer.
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);
    
    std::string vertexShader =
         "#version 330 core\n"
         "layout (location = 0) in vec3 aPos;\n"
         "void main()\n"
         "{\n"
         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
         "}\0";
    
    
    std::string fragmentShader =
         "#version 330 core\n"
         "out vec4 FragColor;\n"
         "void main()\n"
         "{\n"
         "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
         "}\n\0";


    
    
    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);
    
    while(!glfwWindowShouldClose(window)){
        
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        // Draw to screen
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
    }
    
    glDeleteProgram(shader);
    
    glfwTerminate();
    
    return 0;
}
