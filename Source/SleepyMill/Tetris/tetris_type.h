#pragma once
#include "Cell/AvailableChar.h"
#include "SleepyMill/spring_utils.h"


class APlayerPawn;

namespace tetris
{
	struct grid_t
	{
		int grid_width = 0;
		int grid_height = 0;
		TMap<FVector, Fgrid_data_t> grid;
	};

	struct player_t
	{
		TSoftObjectPtr<APlayerPawn> player;
	};

	struct tetris_score_t
	{
		float true_score;
		float display_score;
		
		spring_utils::damped_spring_params_t spring_params;
		spring_utils::damped_spring_float_t spring_data;
		float damping_ratio = 0.0;
		float frequency = 0.0;
		float angular_goal = 0.0;;
	};
}

