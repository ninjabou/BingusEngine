#include "GraphicsManager.h"
#include "Types.h"
#include <chrono>
#include <thread>

using namespace std::literals::chrono_literals;

namespace bingusengine {
    class Engine {
        public:
            GraphicsManager graphics;
            // InputManager input
        
            void Start( /*GameParameters, SetupCallback, UpdateCallback*/ ){
                graphics.Start();
                this->GameLoop();
            }

            void Shutdown(){
                graphics.Shutdown();
            }

            void GameLoop(){
                while(true){
                    // input.Update()
                    
                    // UpdateCallback()
                    
                    // graphics.Draw()
                    
                    // Manage timestep
                    // TEMP FIXED timestep of 1/10 seconds.
                    // Implement delta time at some point...
                    using clock = std::chrono::steady_clock;
                    clock::time_point next_time_point = clock::now() + 100ms;

                    std::this_thread::sleep_until(next_time_point);
                }
            }
    };
}