#pragma once
#include "Shape/shape_type.h"
#include "SleepyMill/flecs/flecs.h"

namespace flecs::ue
{
	struct entity_link_t;
}

namespace tetris
{
	void current_shape_movement_system(flecs::iter it, tetris::current_shape_t* current_shape);
}

