#include "cell_utils.h"

#include "cell_type.h"
#include "SleepyMill/unreal_utils.h"
#include "SleepyMill/flecs/flecs.h"


FString tetris::get_random_character(flecs::world* world, float vowel_rate)
{
	const tetris::global_cell_character_t* global_char = world->get<tetris::global_cell_character_t>();
	if (global_char == nullptr)
		return FString("Err");

	
	if (FMath::FRandRange(0.0, 1.0f) <= vowel_rate)
	{
		return unreal_utils::pick_random(global_char->vowels);
	}

	return unreal_utils::pick_random(global_char->consonants);
}
