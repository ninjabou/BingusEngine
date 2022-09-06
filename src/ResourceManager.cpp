#include "ResourceManager.h"
#include "Engine.h"

namespace bingusengine {
    void ResourceManager::Init(Engine* e, string root){
        this->e = e;
        this->root = root;
    }

    string ResourceManager::ResolvePath(string path){
        return this->root + path;
    }
}