#include <iostream>
#include <Engine.h>

void UpdateCB();

int main( int argc, const char* argv[] ) {
    using namespace bingusengine;

    std::cout << "Hello, World!\n";

    Engine engine;
    engine.Init();
    engine.GameLoop( [&]() {
        if(engine.input.GetKey(KEY_W)){
            std::cout << "⇑\n";
        }
        if(engine.input.GetKey(KEY_A)){
            std::cout << "⇐\n";
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