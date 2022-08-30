#include <iostream>
#include <Engine.h>

int main( int argc, const char* argv[] ) {
    using namespace bingusengine;

    std::cout << "Hello, World!\n";

    Engine engine;
    engine.Start();

    return 0;
}