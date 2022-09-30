#ifndef ECS_H
#define ECS_H

#include "Types.h"
#include <cstdint>
#include <memory>
#include <set>
#include <iostream>

namespace bingusengine {
    class ECS {
        public:
            void Init(Engine *engine){
                e = engine;
            }
            
            void Shutdown(){
                // Shut down.
            }

            class SparseSetHolder {
                public:
                    // A virtual destructor, since we store pointers to this superclass yet have subclasses with destructors that need to run.
                    virtual ~SparseSetHolder() = default;
                    virtual bool Has(EntityID) const = 0;
                    virtual void Drop(EntityID) = 0;
            };

            // Subclasses are templated on the component type they hold.
            template<typename T>
            class SparseSet : public SparseSetHolder {
                public:
                    std::unordered_map<EntityID, T> data;
                    bool Has(EntityID e) const override { return data.count(e) > 0; };
                    void Drop(EntityID e) override { data.erase(e); };
            };

            template<typename T>
            int GetComponentIndex() {
                static int index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
                return index;
            }

            int GetNextIndex() {
                static int index = -1; // Returns the sequence 0, 1, 2, … every time this is called.
                index += 1;
                return index;
            }

            template<typename T>
            std::unordered_map<EntityID, T>&
            GetAppropriateSparseSet() {
                // Get the index for T’s SparseSet
                const int index = GetComponentIndex<T>();
                // If we haven’t seen it yet, it must be past the end.
                // Since component indices are shared by all ECS instances,
                // it could happen that index is more than one past the end.
                if(index >= components.size()) { components.resize(index + 1); }
                assert(index < components.size());
                // Create the actual sparse set if needed.
                if(components[index] == nullptr) components[index] = std::make_unique<SparseSet<T>>();
                // It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
                return static_cast<SparseSet<T>&>(*components[index]).data;
            }

            template<typename T>
            T& Get(EntityID entity) {
                return GetAppropriateSparseSet<T>()[entity];
            }

            template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
            void ForEach( const ForEachCallback& callback ) {
                // Iterate over elements of the first container.
                auto& container = GetAppropriateSparseSet<EntitiesThatHaveThisComponent>();
                for( const auto& [entity, value] : container ) {
                    // We know it has the first component.
                    // Skip the entity if it doesn't have the remaining components.
                    // This `if constexpr` is evaluated at compile time. It is needed when AndAlsoTheseComponents is empty.
                    // https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
                    if constexpr (sizeof...(AndAlsoTheseComponents) > 0) {
                        if( !HasAll<AndAlsoTheseComponents...>( entity ) ) {
                            continue;
                        }
                    }
                    callback( entity );
                }
            }

            // Returns true if the entity has all types.
            template <typename T, typename... Rest>
            bool HasAll( EntityID entity ) {
                bool result = true;
                // https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
                if constexpr (sizeof...(Rest) > 0) { result = HasAll<Rest...>(entity); }
                return result && GetAppropriateSparseSet<T>().count( entity ) > 0;
            }

            // Get an unused ID and add it to the list of known IDs.
            EntityID Create(){
                EntityID assigned_id;

                if(!released_ids.empty()){
                    // we have removed some ids: we use those first.
                    assigned_id = *used_ids.insert(*released_ids.erase(released_ids.begin())).first;
                } else {
                    // we haven't removed any ids yet.
                    if(!used_ids.empty()){
                        // we already have some used ids.
                        assigned_id = *used_ids.insert(*used_ids.rbegin() + 1).first;
                    } else {
                        // this is the first created id.
                        assigned_id = *used_ids.insert(EntityID(1)).first;
                    }
                }

                return assigned_id;
            }
            
            // Destroy the entity by removing all components.
            void Destroy(EntityID entity) {
                used_ids.erase(used_ids.find(entity));
                released_ids.insert(entity);

                for( const auto& comps : components ) { 
                    comps->Drop(entity);
                }
            }

        // This has to be down here so it knows what a SparseSetHolder is...
        private:
            Engine* e = nullptr;
            std::vector<std::unique_ptr<SparseSetHolder>> components;
            
            // a number is added to used_ids when an entity is created,
            // when an entity is destroyed, the number is added to
            // released_ids. create() will then prefer to use the smallest
            // element on released_ids before adding to used_ids.
            // this is done so that we can prioritize low ids.
            std::set<EntityID> used_ids;
            std::set<EntityID> released_ids;
    };
}

#endif