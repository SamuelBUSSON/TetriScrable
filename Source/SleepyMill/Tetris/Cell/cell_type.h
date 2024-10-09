#pragma once
#include "Engine/DataTable.h"

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
}
