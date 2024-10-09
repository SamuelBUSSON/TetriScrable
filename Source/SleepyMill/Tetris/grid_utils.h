#pragma once
#include "SleepyMill/flecs/flecs.h"

namespace tetris
{
	struct grid_t;
}

namespace flecs
{
	struct world;
}

namespace tetris
{
	bool is_pos_occupied(flecs::world* world, FVector position);
	bool is_pos_below_occupied(flecs::world* world, FVector location);
	bool can_go_below(flecs::entity shape_entity);
	bool can_go_left(flecs::entity shape_entity);
	bool can_go_right(flecs::entity shape_entity);
	void check_for_words(flecs::entity shape_entity);
	void add_string(tetris::grid_t* grid, FVector location, FString string);

}
