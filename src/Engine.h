#include "GraphicsManager.h"

namespace bingusengine {
    class Engine {
        public:
            GraphicsManager graphics;
            // InputManager input
        
            void Start( /*GameParameters, SetupCallback, UpdateCallback*/ ){
                graphics.Start();
            }

            void Shutdown(){
                graphics.Shutdown();
            }

            void GameLoop(){
                // while( True ):
                // input.Update()
                
                // UpdateCallback()
                
                // graphics.Draw()
                
                // // Manage timestep
                // random comment to make sure i can actually push
            }
    };
}