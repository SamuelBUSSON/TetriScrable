#pragma once
#include "SleepyMill/flecs/flecs.h"

namespace flecs::ue
{
	struct entity_link_t;
}

namespace tetris
{	
	void tetris_movement_system(flecs::iter it, flecs::ue::entity_link_t* link_a);
}

