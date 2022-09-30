#include "ECS.h"
#include "Engine.h"

namespace bingusengine {
    class SparseSetHolder {
        public:
            // A virtual destructor, since we store pointers to this superclass yet have subclasses with destructors that need to run.
            virtual ~SparseSetHolder() = default;
            virtual bool Has(uint64_t) const = 0;
            virtual void Drop(uint64_t) = 0;
    };

    // Subclasses are templated on the component type they hold.
    template<typename T>
    class SparseSet : public SparseSetHolder {
        public:
            std::unordered_map<uint64_t, T> data;
            bool Has(uint64_t e) const override { return data.count(e) > 0; };
            void Drop(uint64_t e) override { data.erase(e); };
    };

    struct ECS::impl {
        Engine* e = nullptr;

        std::vector<std::unique_ptr<SparseSetHolder>> components;
    };

    int GetNextIndex() {
        static int index = -1; // Returns the sequence 0, 1, 2, … every time this is called.
        index += 1;
        return index;
    }

    template<typename T>
    int GetComponentIndex() {
        static int index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
        return index;
    }

    template<typename T>
    std::unordered_map<uint64_t, T>&
    ECS::GetAppropriateSparseSet() {
        // Get the index for T’s SparseSet
        const int index = GetComponentIndex<T>();
        // If we haven’t seen it yet, it must be past the end.
        // Since component indices are shared by all ECS instances,
        // it could happen that index is more than one past the end.
        if(index >= priv->components.size()) { priv->components.resize(index + 1); }
        assert(index < priv->components.size());
        // Create the actual sparse set if needed.
        if(priv->components[index] == nullptr) priv->components[index] = std::make_unique<SparseSet<T>>();
        // It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
        return static_cast<SparseSet<T>&>(*priv->components[index]).data;
    }

    void ECS::Init(Engine *e){
        priv->e = e;
    }

    void ECS::Shutdown(){
        // Shut down.
    }

    

    template<typename T>
    T& ECS::Get(uint64_t entity) {
        return GetAppropriateSparseSet<T>()[entity];
    }

    // Destroy the entity by removing all components.
    void ECS::Destroy(uint64_t entity) {
        for( const auto& comps : priv->components ) { 
            comps->Drop(entity);
        }
    }

    template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
    void ECS::ForEach( const ForEachCallback& callback ) {
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
    bool ECS::HasAll( uint64_t entity ) {
        bool result = true;
        // https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
        if constexpr (sizeof...(Rest) > 0) { result = HasAll<Rest...>(entity); }
        return result && GetAppropriateSparseSet<T>().count( entity ) > 0;
    }

    ECS::ECS() : priv(std::make_unique<impl>()){}
    ECS::~ECS() = default;
}