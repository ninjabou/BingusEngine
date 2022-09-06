#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Types.h"
#include <memory>

namespace SoLoud{
    class Soloud;
}

namespace bingusengine {
    class AudioManager {
        private:
            Engine* e;
            std::unique_ptr<SoLoud::Soloud> soloud;

        public:
            void Init(Engine* e);

            ~AudioManager();
    };
}

#endif