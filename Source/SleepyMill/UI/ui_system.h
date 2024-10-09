#pragma once

struct ui_t;
#include "SleepyMill/flecs/flecs.h"

namespace ui
{
	void update_game_ui(flecs::iter it, ui_t* ui_a);
}
