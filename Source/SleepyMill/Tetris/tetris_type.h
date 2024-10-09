#pragma once
#include "SleepyMill/flecs/flecs.h"

namespace tetris
{
	struct tetris_square_t
	{
		
	};

	struct tetris_shape_t
	{
		TArray<flecs::entity> square_entity;
	};
}

