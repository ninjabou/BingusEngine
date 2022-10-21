#include <iostream>
#include <Engine.h>

int main( int argc, const char* argv[] ) {
    using namespace bingusengine;

    std::cout << "Hello, World!\n";

    Engine e;
    e.Init();
    e.audio.LoadSound("yahoo", "assets/mk64_toad03.wav");
    e.graphics.LoadImage("toad", "assets/toad.png");
    e.graphics.LoadImage("rocket", "assets/rocket.png");
    e.scripts.LoadScript("controls", "assets/controls.lua");

    EntityID toad1 = e.ecs.Create();
    e.ecs.Get<Position>(toad1).x = 10;
    e.ecs.Get<Position>(toad1).y = 10;
    e.ecs.Get<Sprite>(toad1).z = 0.;
    e.ecs.Get<Sprite>(toad1).scale = 20.;
    e.ecs.Get<Sprite>(toad1).name = "toad";

    // EntityID toad2 = e.ecs.Create();
    // e.ecs.Get<Position>(toad2).x = -30;
    // e.ecs.Get<Position>(toad2).y = -20;
    // e.ecs.Get<Sprite>(toad2).z = -1.;
    // e.ecs.Get<Sprite>(toad2).scale = 10.;
    // e.ecs.Get<Sprite>(toad2).name = "rocket";
    // e.ecs.Get<Script>(toad2).name = "controls";

    // test to make sure ECS.Destroy() works, should not render!
    EntityID toad3 = e.ecs.Create();
    e.ecs.Get<Position>(toad3).x = -30;
    e.ecs.Get<Position>(toad3).y = 20;
    e.ecs.Get<Sprite>(toad3).z = 1.;
    e.ecs.Get<Sprite>(toad3).scale = 10.;
    e.ecs.Get<Sprite>(toad3).name = "toad";
    e.ecs.Destroy(toad3);
    
    e.GameLoop( [&]() {
        // if(e.input.GetKey(KEY_W)){
        //     e.ecs.Get<Position>(toad2).y += 1;
        // }
        // if(e.input.GetKey(KEY_A)){
        //     e.ecs.Get<Position>(toad2).x -= 1;
        // }
        // if(e.input.GetKey(KEY_S)){
        //     e.ecs.Get<Position>(toad2).y -= 1;
        // }
        // if(e.input.GetKey(KEY_D)){
        //     e.ecs.Get<Position>(toad2).x += 1;
        // }
    } );

    return 0;
}