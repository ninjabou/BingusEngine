#ifndef ECS_H
#define ECS_H

#include "Types.h"
#include <cstdint>
#include <memory>

namespace bingusengine {
    class ECS {
        private:
            struct impl;
            std::unique_ptr<impl> priv;

        public:
            void Init(Engine* e);
            void Shutdown();
            
            template<typename T> T& Get(uint64_t entity);
            
            void Destroy(uint64_t entity);

            template<typename T>
            std::unordered_map<uint64_t, T>&
            GetAppropriateSparseSet();

            template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
            void ForEach( const ForEachCallback& callback );

            template <typename T, typename... Rest>
            bool HasAll( uint64_t entity );

            ECS();
            ~ECS();
    };
}

#endif