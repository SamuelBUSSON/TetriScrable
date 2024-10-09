#pragma once
#include "Cell/AvailableChar.h"


class APlayerPawn;

namespace tetris
{
	struct grid_t
	{
		int grid_width = 0;
		int grid_height = 0;
		TMap<FVector2d, Fgrid_data_t> grid;
	};

	struct player_t
	{
		TSoftObjectPtr<APlayerPawn> player;
	};
}

