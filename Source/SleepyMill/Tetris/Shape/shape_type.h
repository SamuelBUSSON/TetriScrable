#pragma once
#include "SleepyMill/spring_utils.h"
#include "SleepyMill/flecs/flecs.h"

namespace tetris
{
	struct shape_init_t	{	};

	struct shape_t
	{
		TArray<flecs::entity> cell_entity;
	};

	struct shape_movement_params_t
	{
		spring_utils::damped_spring_params_t spring_params;
		spring_utils::damped_spring_vector_t spring_data;
		float damping_ratio = 0.0;
		float frequency = 0.0;
	};

	struct current_shape_t
	{
		AActor* shape_actor = nullptr;
		flecs::entity shape_entity = {};
		FVector goal = {};
	};
}
