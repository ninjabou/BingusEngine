#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Types.h"

namespace bingusengine {
    class ResourceManager {
        private:
            Engine* e;
            string root;

        public:
            void Init(Engine* e, string root);
            string ResolvePath(string path);
    };
}

#endif