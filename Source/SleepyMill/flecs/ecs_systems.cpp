#include "ecs_systems.h"

#include "ue_flecs.h"
#include "SleepyMill/Tetris/tetris_system.h"

void ecs::init_system(flecs::world* world)
{
	world->system<flecs::ue::entity_link_t>().iter(tetris::tetris_movement_system);
}
