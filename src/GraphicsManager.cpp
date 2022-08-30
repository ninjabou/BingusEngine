#define GLFW_INCLUDE_NONE
#include "GraphicsManager.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace bingusengine {
    void GraphicsManager::Start(){
        int window_width = 1200;
        int window_height = 800;

        glfwInit();
        // We'll use sokol_gfx's OpenGL backend
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        GLFWwindow* window = glfwCreateWindow( window_width, window_height, "Bingus Engine", /*fullscreen?*/false ? glfwGetPrimaryMonitor() : 0, 0 );
        glfwSetWindowAspectRatio( window, window_width, window_height );
        if( !window )
        {
            std::cerr << "Failed to create a window." << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent( window );
        glfwSwapInterval(1);
    }
}