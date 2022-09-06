#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Types.h"

namespace bingusengine {
    class InputManager {
        private:
            Engine* e;
            float axis_x;
            float axis_y;

        public:
            void Init(Engine *e);
            void Update();
            bool GetKey(int key);
            int GetXAxis();
            int GetYAxis();
    };
}

#endif