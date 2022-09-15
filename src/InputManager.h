#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Types.h"

namespace bingusengine {
    class InputManager {
        private:
            Engine* e;
            float axis_x;
            float axis_y;
            int key_states[KEY_LAST];

        public:
            void Init(Engine *e);
            void Update();
            bool GetKey(int key);
            bool GetKeyDown(int key);
            bool GetKeyUp(int key);
            int GetXAxis();
            int GetYAxis();
    };
}

#endif