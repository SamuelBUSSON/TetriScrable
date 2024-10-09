#include "shape_system.h"

#include "shape_type.h"
#include "Components/TextRenderComponent.h"
#include "SleepyMill/flecs/FlecsAuthoringComponent.h"
#include "SleepyMill/flecs/FlecsEntity.h"
#include "SleepyMill/flecs/ue_flecs.h"
#include "SleepyMill/Player/PlayerPawn.h"
#include "SleepyMill/Tetris/tetris_type.h"
#include "SleepyMill/Tetris/Cell/cell_type.h"


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

				shape.cell_actor.Add(child_actor);
			}

			if (shape.cell_entity.Num() > 0)
				it.entity(idx).add<tetris::shape_init_t>();
		}
	}

	void cell_rotation(flecs::iter it, tetris::cell_t* cell_a, flecs::ue::entity_link_t* link_a)
	{
		auto world = it.world();
		APlayerPawn* player_pawn = world.get<player_t>()->player.Get();
		FVector player_loc = player_pawn->GetActorLocation();
		
		for (int idx : it)
		{
			tetris::cell_t& cell = cell_a[idx];
			UTextRenderComponent* text_render = cell.text_render.Get();
			FVector to_cam = player_loc - text_render->GetComponentLocation();
			to_cam.Z = 0.0;
			to_cam.Y = 0.0;
			text_render->SetWorldRotation(to_cam.Rotation());
			
		}
	}

	void cell_scale(flecs::iter it, tetris::cell_scale_t* cell_scale_a, flecs::ue::entity_link_t* link_a)
	{
		float dt = it.delta_time();
		for (int idx : it)
		{
			AActor* actor = link_a[idx].actor;
			cell_scale_t& cell_scale = cell_scale_a[idx];
			spring_utils::calc_damped_spring_motion_params(cell_scale.spring_params, dt, cell_scale.frequency, cell_scale.damping_ratio);
			spring_utils::compute_spring_goal_float(cell_scale.goal, cell_scale.spring_data, cell_scale.spring_params);
				
			actor->SetActorScale3D(FVector::One() * cell_scale.spring_data.current_position);
		}
	}
}
