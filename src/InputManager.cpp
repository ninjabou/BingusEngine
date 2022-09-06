#define GLFW_INCLUDE_NONE
#include "InputManager.h"
#include "GLFW/glfw3.h"
#include "Engine.h"
#include <iostream>

namespace bingusengine {
    void InputManager::Init(Engine *e){
        this->e = e;
    }

    void InputManager::Update(){
        glfwPollEvents();
    }

    bool InputManager::GetKey(int key){
        return glfwGetKey((GLFWwindow*)e->graphics.window, key);
    }

    int InputManager::GetXAxis(){
        return glfwGetKey((GLFWwindow*)e->graphics.window, KEY_D) - glfwGetKey((GLFWwindow*)e->graphics.window, KEY_A);
    }

    int InputManager::GetYAxis(){
        return glfwGetKey((GLFWwindow*)e->graphics.window, KEY_W) - glfwGetKey((GLFWwindow*)e->graphics.window, KEY_S);
    }
}