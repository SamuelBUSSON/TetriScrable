#pragma once
#include "SleepyMill/spring_utils.h"
#include "SleepyMill/flecs/flecs.h"

namespace tetris
{
	struct shape_init_t	{	};

	struct shape_t
	{
		TArray<flecs::entity> cell_entity;
		TArray<AActor*> cell_actor;
	};

	struct shape_movement_params_t
	{
		spring_utils::damped_spring_params_t spring_params;
		spring_utils::damped_spring_vector_t spring_data;
		float damping_ratio = 0.0;
		float frequency = 0.0;
		FVector goal = {};
		
		spring_utils::damped_spring_params_t angular_spring_params;
		spring_utils::damped_spring_float_t angular_spring_data;
		float angluar_damping_ratio = 0.0;
		float angluar_frequency = 0.0;
		float angular_goal = 0.0;
	};

	struct current_shape_t
	{
		AActor* shape_actor = nullptr;
		flecs::entity shape_entity = {};
		bool can_move = true;
	};
}
