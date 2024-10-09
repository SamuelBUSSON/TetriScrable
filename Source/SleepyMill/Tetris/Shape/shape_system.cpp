#include "shape_system.h"

#include "shape_type.h"
#include "SleepyMill/flecs/FlecsAuthoringComponent.h"
#include "SleepyMill/flecs/FlecsEntity.h"
#include "SleepyMill/flecs/ue_flecs.h"


namespace tetris
{
	void shape_init(flecs::iter it, tetris::shape_t* shape_a, flecs::ue::entity_link_t* link_a)
	{
		TArray<AActor*> child_actor_temp;
		for (int idx : it)
		{
			tetris::shape_t& shape = shape_a[idx];
			if (shape.cell_entity.Num() != 0)
				continue;

			child_actor_temp.Empty();
			AActor* actor = link_a[idx].actor;
				
			actor->GetAllChildActors(child_actor_temp);

			for (AActor* child_actor : child_actor_temp)
			{
				if (UFlecsEntity* unreal_flecs_entity = child_actor->FindComponentByClass<UFlecsEntity>())
				{
					shape.cell_entity.Add(unreal_flecs_entity->entity);
				}
			}

			if (shape.cell_entity.Num() > 0)
				it.entity(idx).add<tetris::shape_init_t>();
		}
	}
}
