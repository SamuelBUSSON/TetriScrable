#pragma once
#include "SleepyMill/flecs/flecs.h"

namespace flecs::ue
{
	struct entity_link_t;
}

namespace tetris
{
	struct shape_t;
}

namespace tetris
{	
	void shape_init(flecs::iter it, tetris::shape_t* shape_a, flecs::ue::entity_link_t* link_a);
}
