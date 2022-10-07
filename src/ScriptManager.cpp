#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>
#include "ScriptManager.h"
#include "Types.h"
#include "Engine.h"

namespace bingusengine{
    struct ScriptManager::impl{
        Engine* e = nullptr;
        sol::state lua;
        std::unordered_map<string, sol::load_result> scripts;
    };
    
    void ScriptManager::Init(Engine* e){
        priv->e = e;
        priv->lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);

        // Begin exposing to lua.

        // INPUT
        priv->lua.new_enum("KEYBOARD",
            "W", KEY_W,
            "A", KEY_A,
            "S", KEY_S,
            "D", KEY_D,
            "SPACE", KEY_SPACE,
            "ESC", KEY_ESCAPE
        );
        priv->lua.set_function("GetKey", [&](const int keycode){
            return priv->e->input.GetKey(keycode);
        });
        priv->lua.set_function("GetKeyDown", [&](const int keycode){
            return priv->e->input.GetKeyDown(keycode);
        });
        priv->lua.set_function("GetKeyUp", [&](const int keycode){
            return priv->e->input.GetKeyUp(keycode);
        });

        // QUIT
        priv->lua.set_function("Quit", [&](){
            return priv->e->Quit();
        });

        // SOUND
        priv->lua.set_function("LoadSound", [&](const string& name, const string& path){
            return priv->e->audio.LoadSound(name, path);
        });
        priv->lua.set_function("PlaySound", [&](const string& name){
            return priv->e->audio.PlaySound(name);
        });

        // ECS
        priv->lua.set_function("CreateEntity", [&](){
            return priv->e->ecs.Create();
        });
        priv->lua.set_function("DestroyEntity", [&](EntityID entity){
            return priv->e->ecs.Destroy(entity);
        });
        priv->lua.new_usertype<Position>("Position",
            sol::constructors<Position()>(), 
            "x", &Position::x,
            "y", &Position::y
        );
        priv->lua.set_function("GetPosition", [&](EntityID entity) -> Position& {
            return priv->e->ecs.Get<Position>(entity);
        });
        priv->lua.new_usertype<Velocity>("Velocity",
            sol::constructors<Velocity()>(), 
            "x", &Velocity::x,
            "y", &Velocity::y
        );
        priv->lua.set_function("GetVelocity", [&](EntityID entity) -> Velocity& {
            return priv->e->ecs.Get<Velocity>(entity);
        });
        priv->lua.new_usertype<Gravity>("Gravity",
            sol::constructors<Gravity()>(), 
            "meters_per_second", &Gravity::meters_per_second
        );
        priv->lua.set_function("GetGravity", [&](EntityID entity) -> Gravity& {
            return priv->e->ecs.Get<Gravity>(entity);
        });
        priv->lua.new_usertype<Health>("Health",
            sol::constructors<Health()>(), 
            "percent", &Health::percent
        );
        priv->lua.set_function("GetHealth", [&](EntityID entity) -> Health& {
            return priv->e->ecs.Get<Health>(entity);
        });
        priv->lua.new_usertype<Script>("Script",
            sol::constructors<Script()>(), 
            "name", &Script::name
        );
        priv->lua.set_function("GetScript", [&](EntityID entity) -> Script& {
            return priv->e->ecs.Get<Script>(entity);
        });
        priv->lua.new_usertype<Sprite>("Sprite",
            sol::constructors<Sprite()>(), 
            "name", &Sprite::name,
            "offset", &Sprite::offset,
            "scale", &Sprite::scale,
            "rotation", &Sprite::rotation,
            "z", &Sprite::z
        );
        priv->lua.set_function("GetSprite", [&](EntityID entity) -> Sprite& {
            return priv->e->ecs.Get<Sprite>(entity);
        });

        // VECTORS
        priv->lua.new_usertype<glm::vec3>("vec3",
            sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
            "x", &glm::vec3::x,
            "y", &glm::vec3::y,
            "z", &glm::vec3::z,
            // optional and fancy: operator overloading. see: https://github.com/ThePhD/sol2/issues/547
            sol::meta_function::addition, sol::overload( [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1+v2; } ),
            sol::meta_function::subtraction, sol::overload( [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1-v2; } ),
            sol::meta_function::multiplication, sol::overload(
                [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1*v2; },
                [](const glm::vec3& v1, float f) -> glm::vec3 { return v1*f; },
                [](float f, const glm::vec3& v1) -> glm::vec3 { return f*v1; }
            )
        );
        priv->lua.new_usertype<glm::vec2>("vec2",
            sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
            "x", &glm::vec2::x,
            "y", &glm::vec2::y,
            // optional and fancy: operator overloading. see: https://github.com/ThePhD/sol2/issues/547
            sol::meta_function::addition, sol::overload( [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1+v2; } ),
            sol::meta_function::subtraction, sol::overload( [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1-v2; } ),
            sol::meta_function::multiplication, sol::overload(
                [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 { return v1*v2; },
                [](const glm::vec2& v1, float f) -> glm::vec2 { return v1*f; },
                [](float f, const glm::vec2& v1) -> glm::vec2 { return f*v1; }
            )
        );
    }

    bool ScriptManager::LoadScript(const string& name, const string& path){
        priv->scripts[name] = priv->lua.load_file(path);

        // load failed
        if(!priv->scripts[name].valid()){
            // remove it from the map.
            priv->scripts.erase(name);
            return false;
        }
        return true;
    }

    void ScriptManager::Update(){
        priv->e->ecs.ForEach<Script>([&](EntityID entity){
            Script script = priv->e->ecs.Get<Script>(entity);
            priv->scripts.at(script.name)(entity);
        });
    }

    ScriptManager::ScriptManager() : priv(std::make_unique<impl>()){}
    ScriptManager::~ScriptManager() = default;
}