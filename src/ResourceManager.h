#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Types.h"

namespace bingusengine {
    class ResourceManager {
        // TO BE REPLACED WITH PIMPL
        private:
            Engine* e = nullptr;
            string root;

        public:
            void Init(Engine* e, string root);
            string ResolvePath(string path);
    };
}

#endif