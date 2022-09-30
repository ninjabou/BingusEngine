#include <iostream>
#include <Engine.h>

int main( int argc, const char* argv[] ) {
    using namespace bingusengine;

    std::cout << "Hello, World!\n";

    Engine e;
    e.Init();
    e.audio.LoadSound("yahoo", "assets/mk64_toad03.wav");
    e.graphics.LoadImage("toad", "assets/toad.png");

    EntityID toad1 = e.ecs.Create();
    e.ecs.Get<Position>(toad1).x = 10;
    e.ecs.Get<Position>(toad1).y = 10;
    e.ecs.Get<Sprite>(toad1).z = 1.;
    e.ecs.Get<Sprite>(toad1).scale = 20.;
    e.ecs.Get<Sprite>(toad1).name = "toad";

    EntityID toad2 = e.ecs.Create();
    e.ecs.Get<Position>(toad2).x = -30;
    e.ecs.Get<Position>(toad2).y = -20;
    e.ecs.Get<Sprite>(toad2).z = 1.;
    e.ecs.Get<Sprite>(toad2).scale = 10.;
    e.ecs.Get<Sprite>(toad2).name = "toad";

    // test to make sure ECS.Destroy() works, should not render!
    EntityID toad3 = e.ecs.Create();
    e.ecs.Get<Position>(toad3).x = -30;
    e.ecs.Get<Position>(toad3).y = 20;
    e.ecs.Get<Sprite>(toad3).z = 1.;
    e.ecs.Get<Sprite>(toad3).scale = 10.;
    e.ecs.Get<Sprite>(toad3).name = "toad";
    e.ecs.Destroy(toad3);
    
    e.GameLoop( [&]() {

        if(e.input.GetKeyDown(KEY_W)){
            std::cout << "⇑\n";
        }
        if(e.input.GetKeyDown(KEY_A)){
            std::cout << "⇐\n";
            e.audio.PlaySound("yahoo");
        }
        if(e.input.GetKeyDown(KEY_S)){
            std::cout << "⇓\n";
        }
        if(e.input.GetKeyDown(KEY_D)){
            std::cout << "⇒\n";
        }
        if(e.input.GetKey(KEY_W)){
            e.ecs.Get<Position>(toad2).y += 1;
        }
        if(e.input.GetKey(KEY_A)){
            e.ecs.Get<Position>(toad2).x -= 1;
        }
        if(e.input.GetKey(KEY_S)){
            e.ecs.Get<Position>(toad2).y -= 1;
        }
        if(e.input.GetKey(KEY_D)){
            e.ecs.Get<Position>(toad2).x += 1;
        }
    } );

    return 0;
}