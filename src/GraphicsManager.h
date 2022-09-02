#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "Types.h"

namespace bingusengine {
    class GraphicsManager {
        friend class InputManager;

        private:
            // Unfortunately must be a void* for now,
            // may change if I implement pimpl pattern.
            void* window;
            int window_width;
            int window_height;
            Engine* e;

        public:
            void Init(Engine* e, int win_w, int win_h);
            void Shutdown();
            void Draw();
            bool ShouldQuit();
    };
}

#endif