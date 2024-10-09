// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonFunctionLibrary.h"

#include "tetris_type.h"
#include "SleepyMill/flecs/ue_flecs.h"

float UCommonFunctionLibrary::get_current_score(UObject* world_context)
{
	if (world_context == nullptr)
		return 0.0;

	flecs::world* flecs_world = flecs::ue::get_world(world_context->GetWorld());
	if (auto score = flecs_world->get<tetris::tetris_score_t>())
	{
		return score->display_score;
	}

	return 0.0;
}
