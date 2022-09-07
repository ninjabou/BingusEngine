#include <iostream>
#include <Engine.h>

int main( int argc, const char* argv[] ) {
    using namespace bingusengine;

    std::cout << "Hello, World!\n";

    Engine engine;
    engine.Init();
    engine.audio.LoadSound("yahoo", "assets/mk64_toad03.wav");

    // temporary measure for checkpoint 4.
    // InputManager will eventually have GetKeyDown.
    bool press_a_last_frame = false;
    
    engine.GameLoop( [&]() {
        if(engine.input.GetKey(KEY_W)){
            std::cout << "⇑\n";
        }
        if(engine.input.GetKey(KEY_A)){
            std::cout << "⇐\n";
            if(!press_a_last_frame){
                press_a_last_frame = true;
                engine.audio.PlaySound("yahoo");
            }
        } else {
            press_a_last_frame = false;
        }
        if(engine.input.GetKey(KEY_S)){
            std::cout << "⇓\n";
        }
        if(engine.input.GetKey(KEY_D)){
            std::cout << "⇒\n";
        }
        if(engine.input.GetXAxis() && engine.input.GetYAxis()){
            std::cout << "diagonal pressed!\n";
        }
    } );

    return 0;
}