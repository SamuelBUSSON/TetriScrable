#include "tetris_system.h"

#include "grid_utils.h"
#include "tetris_type.h"
#include "Cell/cell_type.h"
#include "SleepyMill/spring_utils.h"
#include "SleepyMill/unreal_utils.h"
#include "SleepyMill/flecs/ue_flecs.h"
#include "SleepyMill/Player/PlayerPawn.h"

namespace tetris
{
	void current_shape_movement_system(flecs::iter it, tetris::current_shape_t* current_shape)
	{
		flecs::world world = it.world();
		const player_t* player = world.get<player_t>();

		if (player == nullptr)
			return;

		APlayerPawn* player_pawn = player->player.Get();
		UWorld* u_world = player_pawn->GetWorld();

		grid_t* grid = world.get_mut<grid_t>();
		float dt = it.delta_time();
		
		// Spawn new shape if there is no current shape
		if (current_shape->shape_actor == nullptr)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			FVector spawn_pos = player_pawn->GetActorLocation() + player_pawn->GetActorForwardVector() * 200 + FVector(0,0,1) * grid->grid_height / 2.0;
			spawn_pos.Y = FMath::RoundToInt(spawn_pos.Y);
			spawn_pos.Z = FMath::RoundToInt(spawn_pos.Z);
			FVector spawn_dir = spawn_pos - player_pawn->GetActorLocation();
			spawn_dir.Z = 0;
			spawn_dir.Normalize();
			FRotator spawn_rot = spawn_dir.Rotation() + FRotator(0, 90, 0);
			
			current_shape->shape_actor = u_world->SpawnActor(unreal_utils::pick_random(player_pawn->shape_list), &spawn_pos, &spawn_rot, SpawnInfo);			
			current_shape->shape_entity = flecs::ue::get_entity_from_actor(current_shape->shape_actor);
			return;
		}

		shape_movement_params_t* movement_params = current_shape->shape_entity.get_mut<tetris::shape_movement_params_t>();

		spring_utils::calc_damped_spring_motion_params(movement_params->spring_params, dt, movement_params->frequency, movement_params->damping_ratio);
		spring_utils::compute_spring_goal_vector(movement_params->goal, movement_params->spring_data, movement_params->spring_params);
		current_shape->shape_actor->SetActorLocation(movement_params->spring_data.current_position);
		
		// spring_utils::calc_damped_spring_motion_params(movement_params->angular_spring_params, dt, movement_params->angluar_frequency, movement_params->angluar_damping_ratio);
		// spring_utils::compute_spring_goal_float(movement_params->angular_goal, movement_params->angular_spring_data, movement_params->angular_spring_params);
		// FRotator actor_rot = current_shape->shape_actor->GetActorRotation();		
		// current_shape->shape_actor->SetActorRotation(FRotator(movement_params->angular_goal,actor_rot.Yaw,actor_rot.Roll));

		// Is blocked by something or reach the bottom
		if (!current_shape->can_move)
		{
			FVector to_goal = movement_params->goal - movement_params->spring_data.current_position;
			float dist_to_goal = to_goal.Length();
			if (dist_to_goal <= 3)
			{
				current_shape->shape_actor->SetActorLocation(movement_params->goal);
				// todo (sb) : Store cells inside grid
				const shape_t* shape = current_shape->shape_entity.get<shape_t>();
				for (flecs::entity cell_entity : shape->cell_entity)
				{
					AActor* cell_actor = cell_entity.get<flecs::ue::entity_link_t>()->actor;
					const cell_t* cell_data = cell_entity.get<tetris::cell_t>();
					tetris::add_string(grid, cell_actor->GetActorLocation(), cell_data->current_cell_text);
				}

				tetris::check_for_words(current_shape->shape_entity);
				current_shape->shape_actor = nullptr;
				current_shape->shape_entity = flecs::entity::null();
				current_shape->can_move = true;
			}
		}
	}
}
