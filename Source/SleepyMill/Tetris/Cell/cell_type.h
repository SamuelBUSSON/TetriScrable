#pragma once
#include "Engine/DataTable.h"
#include "SleepyMill/spring_utils.h"

class UTextRenderComponent;

namespace tetris
{
	struct cell_t
	{
		TSoftObjectPtr<UTextRenderComponent> text_render = nullptr;
		FString current_cell_text = FString("");
	};

	struct cell_local_position_t
	{
		int x;
		int y;
	};

	struct global_cell_character_t
	{
		TArray<FString> vowels;
		TArray<FString> consonants;
	};

	struct cell_scale_t
	{
		float goal = 0.0;
		
		spring_utils::damped_spring_params_t spring_params;
		spring_utils::damped_spring_float_t spring_data;
		float damping_ratio = 0.0;
		float frequency = 0.0;
	};
	
	struct global_words_t
	{
		TSoftObjectPtr<UDataTable> character_datatable = nullptr;
	};
}
