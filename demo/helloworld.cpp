#include <iostream>
#include <Engine.h>

int main( int argc, const char* argv[] ) {
    using namespace bingusengine;

    std::cout << "Hello, World!\n";

    Engine engine;
    engine.Init();
    engine.audio.LoadSound("yahoo", "assets/mk64_toad03.wav");
    
    engine.GameLoop( [&]() {
        if(engine.input.GetKeyDown(KEY_W)){
            std::cout << "⇑\n";
        }
        if(engine.input.GetKeyDown(KEY_A)){
            std::cout << "⇐\n";
            engine.audio.PlaySound("yahoo");
        }
        if(engine.input.GetKeyDown(KEY_S)){
            std::cout << "⇓\n";
        }
        if(engine.input.GetKeyDown(KEY_D)){
            std::cout << "⇒\n";
        }
        if(engine.input.GetXAxis() && engine.input.GetYAxis()){
            std::cout << "diagonal pressed!\n";
        }
    } );

    return 0;
}