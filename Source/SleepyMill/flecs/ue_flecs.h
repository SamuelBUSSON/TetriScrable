#pragma once
#include "flecs.h"
#include "Misc/NetworkGuid.h"

class AActor;
class UWorld;

namespace flecs
{
    namespace ue
    {
        struct entity_link_t
        {
            AActor* actor = nullptr;
        };

        struct net_id_t
        {
            bool isReady = false;
            FNetworkGUID value = {};
        };

        flecs::world* get_world(UWorld* uworld);
        flecs::world* get_world(AActor* actor);
        flecs::entity get_entity_from_actor(AActor* actor);
        void destroy_entity(flecs::entity entity);
    }
}
