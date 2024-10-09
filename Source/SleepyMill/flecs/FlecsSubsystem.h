#pragma once

#include "CoreMinimal.h"
#include "FlecsSubsystem.generated.h"

namespace flecs
{
    struct world;
    struct entity;
}

UCLASS()
class UFlecsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    FTickerDelegate on_tick_delegate;
    FTSTicker::FDelegateHandle on_tick_handle;

    bool Tick(float dt);

public:
    flecs::world* world = nullptr;

    virtual void Initialize(FSubsystemCollectionBase& collection) override;
    virtual void Deinitialize() override;
};
