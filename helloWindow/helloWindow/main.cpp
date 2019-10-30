//
//  main.cpp
//  helloWindow
//
//  Created by William Kpabitey Kwabla on 10/22/19.
//  Copyright © 2019 William Kpabitey Kwabla. All rights reserved.
//

// Standard C++ libraries
#include <iostream>

// Third-party libraries
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
    
        return -1;
    }
    
    /* Configure GLFW */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
     /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", nullptr, nullptr);
    
    if(window == NULL){
        std::cout<<"Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
       /* Process input */
        processInput(window);
        
         /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

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
 glfw: whenever the window size changed (by OS or user resize) this callback function executes.                                                                         *
****************************************************************************************/
void framebuffer_size_callback(GLFWwindow *window, int height, int width) {
    
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.

    glViewport(0, 0, height, width);

}
