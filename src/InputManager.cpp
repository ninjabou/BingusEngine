#define GLFW_INCLUDE_NONE
#include "InputManager.h"
#include "GLFW/glfw3.h"
#include "Engine.h"
#include <iostream>

namespace bingusengine {
    void InputManager::Init(Engine *e){
        this->e = e;

        for(int i = 0; i <= KEY_LAST; i++){
            key_states[i] = 0;
        }
    }

    void InputManager::Update(){
        glfwPollEvents();

        for(int i = 0; i <= KEY_LAST; i++){
            if(glfwGetKey((GLFWwindow*)e->graphics.window(), i)){
                if(key_states[i] == 0){
                    key_states[i] = 1;
                } else if(key_states[i] == 1){
                    key_states[i] = 2;
                }
            } else {
                if(key_states[i] == 2){
                    key_states[i] = 3;
                } else if(key_states[i] == 3){
                    key_states[i] = 0;
                }
            }
        }
    }

    bool InputManager::GetKey(int key){
        if(key_states[key] == 1 || key_states[key] == 2){
            return true;
        }
        return false;
    }

    bool InputManager::GetKeyDown(int key){
        if(key_states[key] == 1){
            return true;
        }
        return false;
    }

    bool InputManager::GetKeyUp(int key){
        if(key_states[key] == 3){
            return true;
        }
        return false;
    }

    int InputManager::GetXAxis(){
        return glfwGetKey((GLFWwindow*)e->graphics.window(), KEY_D) - glfwGetKey((GLFWwindow*)e->graphics.window(), KEY_A);
    }

    int InputManager::GetYAxis(){
        return glfwGetKey((GLFWwindow*)e->graphics.window(), KEY_W) - glfwGetKey((GLFWwindow*)e->graphics.window(), KEY_S);
    }
}