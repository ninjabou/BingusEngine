#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Types.h"
#include <memory>

namespace bingusengine {
    class AudioManager {
        private:
            Engine* e = nullptr;
            struct impl;
            std::unique_ptr<impl> pImpl;

        public:
            void Init(Engine* e);
            void Shutdown();
            void LoadSound(const string& name, const string& path);
            void PlaySound(const string& name);

            AudioManager();
            ~AudioManager();
    };
}

#endif