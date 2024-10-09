#include "FlecsSubsystem.h"

#include "ecs_systems.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ue_flecs.h"

void UFlecsSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
    UE_LOG(LogTemp, Log, TEXT("Init Flecs"));

    // sets title in Flecs Explorer
    char* argv[] = {"Sleepy Mill"};
    world = new flecs::world(1, argv);

    on_tick_delegate = FTickerDelegate::CreateUObject(this, &UFlecsSubsystem::Tick);
    on_tick_handle = FTSTicker::GetCoreTicker().AddTicker(on_tick_delegate);

    ecs::init_system(world);

    Super::Initialize(collection);
}

void UFlecsSubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Log, TEXT("Deinit Flecs"));

    FTSTicker::GetCoreTicker().RemoveTicker(on_tick_handle);

    if (world != nullptr)
    {
        delete (world);
        world = nullptr;
    }

    Super::Deinitialize();
}

bool UFlecsSubsystem::Tick(float dt)
{
    if (world == nullptr)
        return true;
    
    world->progress(dt);
    return true;
}
