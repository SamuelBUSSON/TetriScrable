#include "grid_utils.h"

#include "tetris_type.h"
#include "Shape/shape_type.h"
#include "SleepyMill/unreal_utils.h"
#include "SleepyMill/flecs/flecs.h"
#include "SleepyMill/flecs/ue_flecs.h"


namespace tetris
{
	bool is_pos_occupied(flecs::world* world, FVector position)
	{
		const grid_t* grid = world->get<grid_t>();
		if (grid == nullptr)
			return false;

		if (const Fgrid_data_t* cell = grid->grid.Find(position))
		{
			return cell->is_occupied;
		}

		return false;
	}

	void round_location(FVector& location)
	{
		location.X = 0.0;
		location.Y = FMath::RoundToInt(location.Y);
		location.Z = FMath::RoundToInt(location.Z);
	}

	void add_string(tetris::grid_t* grid, FVector location, FString string)
	{
		round_location(location);
		if (Fgrid_data_t* grid_cell = grid->grid.Find(location))
		{
			grid_cell->current_string = string;
			grid_cell->is_occupied = true;
		}
	}

	bool can_go_below(flecs::entity shape_entity)
	{
		flecs::world flecs_world = shape_entity.world();
		const shape_t* shape = shape_entity.get<shape_t>();
		AActor* shape_actor = shape_entity.get<flecs::ue::entity_link_t>()->actor;
		const shape_movement_params_t* shape_movement = shape_entity.get<shape_movement_params_t>();

		for (AActor* cell_actor: shape->cell_actor)
		{
			FVector relative_offset = shape_actor->GetActorLocation() - cell_actor->GetActorLocation();
			FVector cell_goal_location = shape_movement->goal - relative_offset;
			round_location(cell_goal_location);
			if (is_pos_below_occupied(&flecs_world, cell_goal_location))
			{
				return false;
			}
		}

		return true;
	}

	bool is_pos_below_occupied(flecs::world* world, FVector location)
	{
		const grid_t* grid = world->get<grid_t>();
		if (grid == nullptr)
			return false;

		location += FVector(0, 0, -100);
		round_location(location);
		
		if (const Fgrid_data_t* grid_cell = grid->grid.Find(location))
		{
			return grid_cell->is_occupied;
		}

		return false;
	}
}
