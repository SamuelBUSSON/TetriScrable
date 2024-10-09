#pragma once

namespace flecs
{
	struct world;
}

namespace tetris
{
	FString get_random_character(flecs::world* world, float vowel_rate);
}
