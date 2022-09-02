#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Types.h"

namespace bingusengine {
    class InputManager {
        private:
            Engine* e;

        public:
            void Init(Engine *e);
            void Update();
            bool GetKey(int key);
    };
}

#endif