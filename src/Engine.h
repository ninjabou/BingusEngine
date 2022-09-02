#include "GraphicsManager.h"
#include "InputManager.h"
#include "Types.h"
#include <chrono>
#include <thread>

using namespace std::literals::chrono_literals;

namespace bingusengine {
    class Engine {
        public:
            GraphicsManager graphics;
            InputManager input;
        
            void Init( /*GameParameters, SetupCallback, UpdateCallback*/ ){
                graphics.Init(this, 1200, 800);
                input.Init(this);
                // this->GameLoop();
            }

            void Shutdown(){
                graphics.Shutdown();
            }

            void GameLoop(const UpdateCallback& callback){
                while(true){
                    input.Update();
                    
                    callback();
                    
                    graphics.Draw();

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