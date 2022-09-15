#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Types.h"
#include <memory>

namespace bingusengine {
    class InputManager {
        private:
            struct impl;
            std::unique_ptr<impl> priv;

        public:
            void Init(Engine *e);
            void Update();
            bool GetKey(int key);
            bool GetKeyDown(int key);
            bool GetKeyUp(int key);
            int GetXAxis();
            int GetYAxis();

            InputManager();
            ~InputManager();
    };
}

#endif