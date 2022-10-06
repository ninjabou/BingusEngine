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
    }

    bool ScriptManager::LoadScript(const string& name, const string& path){
        priv->scripts[name] = priv->lua.load_file(path);

        // load failed
        if(!priv->scripts[name].valid()){
            // remove it from the map.
            priv->scripts.erase(name);
        }
    }

    void ScriptManager::Update(){
        priv->e->ecs.ForEach<Script>([&](EntityID entity){
            Script script = priv->e->ecs.Get<Script>(entity);
            priv->scripts[script.name](entity);
        });
    }

    ScriptManager::ScriptManager() : priv(std::make_unique<impl>()){}
    ScriptManager::~ScriptManager() = default;
}