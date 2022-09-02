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
        // return false;
    }
}