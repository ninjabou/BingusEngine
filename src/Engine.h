#include "GraphicsManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ResourceManager.h"
#include "Types.h"
#include "glm/glm.hpp"
#include <chrono>
#include <thread>

using namespace std::literals::chrono_literals;

namespace bingusengine {
    class Engine {
        public:
            GraphicsManager graphics;
            InputManager input;
            ResourceManager resources;
            AudioManager audio;
        
            void Init(){
                // Pass a reference to this Engine, so that the
                // managers can access each other.
                graphics.Init(this, 1200, 800);
                input.Init(this);
                resources.Init(this, "assets/");
                audio.Init(this);
            }

            void Shutdown(){
                graphics.Shutdown();
                audio.Shutdown();
                // nothing to shut down for Input yet...
            }

            void GameLoop(const UpdateCallback& callback){
                while(true){
                    // Have input poll the keyboard.
                    input.Update();
                    
                    // Run user code.
                    callback();
                    
                    // Draw to the window.
                    graphics.Draw();

                    // Check if the window was closed.
                    if(graphics.ShouldQuit()){
                        this->Shutdown();
                        return;
                    }
                    
                    // Manage timestep
                    // TEMP FIXED timestep of 1/10 seconds.
                    // Implement delta time at some point...
                    using clock = std::chrono::steady_clock;
                    clock::time_point next_time_point = clock::now() + 15ms;

                    std::this_thread::sleep_until(next_time_point);
                }
            }
    };
}