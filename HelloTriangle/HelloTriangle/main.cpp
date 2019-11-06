//
//  main.cpp
//  HelloTriangle
//
//  Created by William Kpabitey Kwabla on 10/30/19.
//  Copyright © 2019 William Kpabitey Kwabla. All rights reserved.
//

// Standard C++ libraries
#include <iostream>

// Third-party libraries
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader/shader.h"
#include <string>
#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader/shader.h"
#include <string>
#endif



// Function Prototypes
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow *window, int height, int width);


// Constants
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main() {
    
    
    /* Initialize glfw library */
    if(!glfwInit()){
        std::cout<<"glfwInit Failed to initailze" <<std::endl;
        return -1;
    }
    
    /* Configure GLFW */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
     /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Triangle", nullptr, nullptr);
    
    if(window == NULL){
        std::cout<<"Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK) {
        
        std::cout<<"glewInit Failed to initialize"<<std::endl;
        return -1;
    }
    
    
    
    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("/Users/william/Documents/Personal/OpenGL/HelloTriangle/HelloTriangle/shader/shader.vs", "/Users/william/Documents/Personal/OpenGL/HelloTriangle/HelloTriangle/shader/shader.fs");
   
    
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
       /* Process input */
        processInput(window);
        
         /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        // draw our first triangle
        ourShader.use();
        
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    
    glfwTerminate();

    return 0;
}


/*
 process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
 */
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}


/*
 glfw: whenever the window size changed (by OS or user resize) this callback function executes.
 */
void framebuffer_size_callback(GLFWwindow *window, int height, int width) {
    
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.

    glViewport(0, 0, height, width);

}
