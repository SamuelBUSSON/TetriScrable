#include "tetris_system.h"

#include "SleepyMill/flecs/ue_flecs.h"

void tetris::tetris_movement_system(flecs::iter it, flecs::ue::entity_link_t* link_a)
{
	for (int idx : it)
	{
		AActor* actor = link_a[idx].actor;
		UE_LOG(LogTemp, Warning, TEXT("My actor name is %s"), *actor->GetName());
	}
}
