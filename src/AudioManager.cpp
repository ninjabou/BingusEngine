#include "AudioManager.h"
#include "Engine.h"
#include "soloud.h"
#include "soloud_wav.h"
#include <iostream>

namespace bingusengine {
    struct AudioManager::impl{
        SoLoud::Soloud soloud;
        std::unordered_map<string, SoLoud::Wav> sounds;
    };

    void AudioManager::Init(Engine* e){
        this->e = e;
        this->pImpl->soloud.init();
    }

    void AudioManager::Shutdown(){
        this->pImpl->soloud.deinit();
    }

    void AudioManager::LoadSound(const string& name, const string& path){
        int err = this->pImpl->sounds[name].load(path.c_str());
    }

    void AudioManager::PlaySound(const string& name){
        this->pImpl->soloud.play(this->pImpl->sounds[name]);
    }

    // AudioManager::AudioManager(){}
    // AudioManager::~AudioManager(){}

    AudioManager::AudioManager() : pImpl(std::make_unique<impl>()){}
    AudioManager::~AudioManager() = default;
}
