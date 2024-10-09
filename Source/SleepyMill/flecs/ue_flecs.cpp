#include "ue_flecs.h"

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "FlecsSubsystem.h"

namespace flecs
{
    namespace ue
    {
        world* get_world(UWorld* uworld)
        {
            UGameInstance* game_instance = UGameplayStatics::GetGameInstance(uworld);
            if (game_instance == nullptr)
                return nullptr;

            UFlecsSubsystem* flecs_subsystem = game_instance->GetSubsystem<UFlecsSubsystem>();
            if (flecs_subsystem == nullptr)
                return nullptr;

            flecs::world* world = flecs_subsystem->world;
            if (world == nullptr)
                return nullptr;

            return world;
        }

        world* get_world(AActor* actor)
        {
            if (actor == nullptr)
                return nullptr;

            return get_world(actor->GetWorld());
        }
        
        void destroy_entity(flecs::entity entity)
        {
            const entity_link_t* link = entity.get<entity_link_t>();
            if (link != nullptr)
            {
                AActor* actor_to_destroy = link->actor;
                actor_to_destroy->Destroy();
            }

            entity.destruct();
        }
    }
}