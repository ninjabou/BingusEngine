#include "AudioManager.h"
#include "Engine.h"
#include "soloud.h"

namespace bingusengine {
    void AudioManager::Init(Engine* e){
        this->e = e;
        // soloud.reset(SoLoud::Soloud);
        
    }

    AudioManager::~AudioManager(){}
}