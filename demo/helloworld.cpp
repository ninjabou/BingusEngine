#include <iostream>
#include <Engine.h>

void UpdateCB();

int main( int argc, const char* argv[] ) {
    using namespace bingusengine;

    std::cout << "Hello, World!\n";

    Engine engine;
    engine.Init();
    engine.GameLoop( [&]() {
        if(engine.input.GetKey(KEY_A)){
            std::cout << "A key pressed\n";
        }
    } );

    return 0;
}