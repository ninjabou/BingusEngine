// Not sure what the point of this file is yet...
#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "Types.h"

namespace bingusengine {
    class GraphicsManager {
        private:
            int window_width;
            int window_height;

        public:
            GraphicsManager(int ww, int wh);
            void Start();
            void Shutdown();
            void Draw();
    };
}

#endif