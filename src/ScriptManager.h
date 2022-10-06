#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "Types.h"

namespace bingusengine {
    class ScriptManager {
        private:
            struct impl;
            std::unique_ptr<impl> priv;

        public:
            void Init(Engine* e);
            bool LoadScript(const string& name, const string& path);
            void Update();

            ScriptManager();
            ~ScriptManager();
    };
}

#endif