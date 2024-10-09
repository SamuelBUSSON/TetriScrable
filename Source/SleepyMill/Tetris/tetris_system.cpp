#include "tetris_system.h"

#include "tetris_type.h"
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
			FVector spawn_pos = player_pawn->GetActorLocation() + player_pawn->GetActorForwardVector() * 200 + player_pawn->GetActorUpVector() * 100 * grid->grid_height / 2.0;
			spawn_pos.Y = FMath::RoundToInt(spawn_pos.Y);
			spawn_pos.Z = FMath::RoundToInt(spawn_pos.Z);
			FVector spawn_dir = spawn_pos - player_pawn->GetActorLocation();
			spawn_dir.Z = 0;
			spawn_dir.Normalize();
			FRotator spawn_rot = spawn_dir.Rotation() + FRotator(0, 90, 0);
			
			current_shape->shape_actor = u_world->SpawnActor(unreal_utils::pick_random(player_pawn->shape_list), &spawn_pos, &spawn_rot, SpawnInfo);			
			current_shape->shape_entity = flecs::ue::get_entity_from_actor(current_shape->shape_actor);
			current_shape->goal = spawn_pos;
			return;
		}

		shape_movement_params_t* movement_params = current_shape->shape_entity.get_mut<
			tetris::shape_movement_params_t>();

		spring_utils::calc_damped_spring_motion_params(movement_params->spring_params, dt, movement_params->frequency, movement_params->damping_ratio);
		spring_utils::compute_spring_goal_vector(current_shape->goal, movement_params->spring_data, movement_params->spring_params);
		current_shape->shape_actor->SetActorLocation(movement_params->spring_data.current_position);
	}
}
