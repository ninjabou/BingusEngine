#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "Types.h"
#include <memory>

namespace bingusengine {
    // A vertex buffer containing a textured square.
    const float vertices[] = {
        // positions      // texcoords
        -1.0f,  -1.0f,    0.0f,  0.0f,
        1.0f,  -1.0f,    1.0f,  0.0f,
        -1.0f,   1.0f,    0.0f,  1.0f,
        1.0f,   1.0f,    1.0f,  1.0f,
    };

    class GraphicsManager {
        private:
            struct impl;
            std::unique_ptr<impl> priv;

        public:
            void Init(Engine* e, int win_w, int win_h);
            void Shutdown();
            void Draw();
            bool ShouldQuit();

            void* window();

            GraphicsManager();
            ~GraphicsManager();
    };
}

#endif