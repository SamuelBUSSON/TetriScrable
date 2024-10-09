#pragma once

#include "flecs.h"
#include "FlecsAuthoringComponent.generated.h"

namespace flecs
{
    struct world;
    struct entity;
}

UINTERFACE()
class UFlecsAuthoringComponent : public UInterface
{
    GENERATED_BODY()
};

class IFlecsAuthoringComponent
{
    GENERATED_BODY()

public:
    virtual void ConvertToEntityComponent(flecs::world* world, flecs::entity& entity) = 0;
};
