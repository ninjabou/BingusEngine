#include "AudioManager.h"
#include "Engine.h"
#include "soloud.h"
#include "soloud_wav.h"
#include <iostream>

namespace bingusengine {
    struct AudioManager::impl{
        Engine* e = nullptr;
        SoLoud::Soloud soloud;
        std::unordered_map<string, SoLoud::Wav> sounds;
    };

    void AudioManager::Init(Engine* e){
        priv->e = e;
        priv->soloud.init();
    }

    void AudioManager::Shutdown(){
        priv->soloud.deinit();
    }

    void AudioManager::LoadSound(const string& name, const string& path){
        int err = priv->sounds[name].load(path.c_str());
    }

    void AudioManager::PlaySound(const string& name){
        priv->soloud.play(priv->sounds[name]);
    }

    AudioManager::AudioManager() : priv(std::make_unique<impl>()){}
    AudioManager::~AudioManager() = default;
}
