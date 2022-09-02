#define GLFW_INCLUDE_NONE
#include "GraphicsManager.h"
#include "GLFW/glfw3.h"
#include "Engine.h"
#include <iostream>

namespace bingusengine {
    void GraphicsManager::Init(Engine* e, int win_w, int win_h){
        
        /* Initialize Class members.
         */
        this->window_width = win_w;
        this->window_height = win_h;
        this->e = e;

        /* Set up GLFW and open a window.
         */
        glfwInit();
        // We'll use sokol_gfx's OpenGL backend
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        this->window = glfwCreateWindow( this->window_width, this->window_height, "Bingus Engine", /*fullscreen?*/false ? glfwGetPrimaryMonitor() : 0, 0 );
        glfwSetWindowAspectRatio( (GLFWwindow*)this->window, this->window_width, this->window_height );
        if( !this->window )
        {
            std::cerr << "Failed to create a window." << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent( (GLFWwindow*)this->window );
        glfwSwapInterval(1);
    }

    void GraphicsManager::Shutdown(){
        glfwTerminate();
    }

    void GraphicsManager::Draw(){
        // wawawawawawawawa (not yet implemented...)
    }

    bool GraphicsManager::ShouldQuit(){
        return glfwWindowShouldClose((GLFWwindow*)this->window);
    }
}