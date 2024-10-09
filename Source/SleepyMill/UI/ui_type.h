#pragma once
#include "SleepyMill/spring_utils.h"
#include "SleepyMill/flecs/flecs.h"

class UTextBlock;

struct ui_t
{
	TSoftObjectPtr<UTextBlock> main_score = nullptr;
	TSoftObjectPtr<UTextBlock> add_score = nullptr;

	
	spring_utils::damped_spring_params_t main_spring_params;
	spring_utils::damped_spring_vector_2d_t main_spring_data;
	float main_damping_ratio = 0.0;
	float main_frequency = 0.0;
	FVector2d main_goal = {};
	
	spring_utils::damped_spring_params_t add_score_spring_params;
	spring_utils::damped_spring_vector_2d_t add_score_spring_data;
	float add_score_damping_ratio = 0.0;
	float add_score_frequency = 0.0;
	FVector2d add_score_goal = {};
};

struct ui_global_t
{
	flecs::entity main_ui;
};
