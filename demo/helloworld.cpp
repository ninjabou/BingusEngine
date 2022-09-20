#include <iostream>
#include <Engine.h>

int main( int argc, const char* argv[] ) {
    using namespace bingusengine;

    std::cout << "Hello, World!\n";

    Engine engine;
    engine.Init();
    engine.audio.LoadSound("yahoo", "assets/mk64_toad03.wav");
    engine.graphics.LoadImage("toad", "assets/toad.png");

    Sprite toad_spr;
    toad_spr.position = vec2(10, 10);
    toad_spr.z = 1.;
    toad_spr.scale = 20.;
    toad_spr.name = "toad";

    Sprite toad_spr2;
    toad_spr2.position = vec2(-30, -20);
    toad_spr2.z = 1.;
    toad_spr2.scale = 10.;
    toad_spr2.name = "toad";

    std::vector<Sprite> sprites;
    sprites.push_back(toad_spr);
    sprites.push_back(toad_spr2);
    
    engine.GameLoop( [&]() {
        engine.graphics.Draw(sprites);

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
        if(engine.input.GetKey(KEY_W)){
            sprites[1].position.y += 1;
        }
        if(engine.input.GetKey(KEY_A)){
            sprites[1].position.x -= 1;
        }
        if(engine.input.GetKey(KEY_S)){
            sprites[1].position.y -= 1;
        }
        if(engine.input.GetKey(KEY_D)){
            sprites[1].position.x += 1;
        }
    } );

    return 0;
}