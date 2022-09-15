#define GLFW_INCLUDE_NONE
#include "InputManager.h"
#include "GLFW/glfw3.h"
#include "Engine.h"
#include <iostream>

namespace bingusengine {
    struct InputManager::impl{
        Engine* e = nullptr;
        float axis_x;
        float axis_y;

        // 0: Not Pressed
        // 1: Just Pressed
        // 2: Currently Held
        // 3: Just Released
        int key_states[KEY_LAST];
    };

    void InputManager::Init(Engine *e){
        priv->e = e;

        for(int i = 0; i <= KEY_LAST; i++){
            priv->key_states[i] = 0;
        }
    }

    void InputManager::Update(){
        glfwPollEvents();

        for(int i = 0; i <= KEY_LAST; i++){
            if(glfwGetKey((GLFWwindow*)priv->e->graphics.window(), i)){
                if(priv->key_states[i] == 0){
                    priv->key_states[i] = 1;
                } else if(priv->key_states[i] == 1){
                    priv->key_states[i] = 2;
                }
            } else {
                if(priv->key_states[i] == 2){
                    priv->key_states[i] = 3;
                } else if(priv->key_states[i] == 3){
                    priv->key_states[i] = 0;
                }
            }
        }
    }

    bool InputManager::GetKey(int key){
        if(priv->key_states[key] == 1 || priv->key_states[key] == 2){
            return true;
        }
        return false;
    }

    bool InputManager::GetKeyDown(int key){
        if(priv->key_states[key] == 1){
            return true;
        }
        return false;
    }

    bool InputManager::GetKeyUp(int key){
        if(priv->key_states[key] == 3){
            return true;
        }
        return false;
    }

    int InputManager::GetXAxis(){
        return glfwGetKey((GLFWwindow*)priv->e->graphics.window(), KEY_D) - glfwGetKey((GLFWwindow*)priv->e->graphics.window(), KEY_A);
    }

    int InputManager::GetYAxis(){
        return glfwGetKey((GLFWwindow*)priv->e->graphics.window(), KEY_W) - glfwGetKey((GLFWwindow*)priv->e->graphics.window(), KEY_S);
    }

    InputManager::InputManager() : priv(std::make_unique<impl>()){}
    InputManager::~InputManager() = default;
}