#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Types.h"
#include <memory>

namespace bingusengine {
    class AudioManager {
        private:
            struct impl;
            std::unique_ptr<impl> priv;

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