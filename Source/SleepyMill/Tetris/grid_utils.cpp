#include "grid_utils.h"

#include "tetris_type.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Cell/cell_type.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Shape/shape_type.h"
#include "SleepyMill/unreal_utils.h"
#include "SleepyMill/flecs/flecs.h"
#include "SleepyMill/flecs/ue_flecs.h"
#include "SleepyMill/Player/PlayerPawn.h"
#include "SleepyMill/UI/ui_type.h"


namespace tetris
{
	bool is_pos_occupied(flecs::world* world, FVector position, flecs::entity& entity_inside)
	{
		const grid_t* grid = world->get<grid_t>();
		if (grid == nullptr)
			return false;

		if (const Fgrid_data_t* cell = grid->grid.Find(position))
		{
			entity_inside = cell->occupied_entity;
			return cell->is_occupied;
		}

		return false;
	}

	void round_location(FVector& location)
	{
		location.X = 0.0;
		location.Y = FMath::RoundToInt(location.Y);
		location.Z = FMath::RoundToInt(location.Z);
	}

	void add_string(tetris::grid_t* grid, FVector location, FString string, AActor* occupied_actor, flecs::entity entity)
	{
		round_location(location);
		if (Fgrid_data_t* grid_cell = grid->grid.Find(location))
		{
			grid_cell->current_string = string;
			grid_cell->is_occupied = true;
			grid_cell->occupied_actor = occupied_actor;
			grid_cell->occupied_entity = entity;
		}
	}

	bool is_game_over(flecs::world* world)
	{
		const ui_global_t* ui_global = world->get<ui_global_t>();
		return ui_global->is_game_over;
	}

	bool can_go_below(flecs::entity shape_entity)
	{
		flecs::world flecs_world = shape_entity.world();
		const shape_t* shape = shape_entity.get<shape_t>();
		AActor* shape_actor = shape_entity.get<flecs::ue::entity_link_t>()->actor;
		const shape_movement_params_t* shape_movement = shape_entity.get<shape_movement_params_t>();

		const grid_t* grid = flecs_world.get<grid_t>();
		const player_t* player = flecs_world.get<player_t>();
		float min_height = player->player->GetActorLocation().Z - grid->grid_height / 2.0;

		for (AActor* cell_actor: shape->cell_actor)
		{
			FVector relative_offset = shape_actor->GetActorLocation() - cell_actor->GetActorLocation();
			FVector cell_goal_location = shape_movement->goal - relative_offset;
			if (cell_goal_location.Z <= min_height)
				return false;
				
			round_location(cell_goal_location);
			flecs::entity touch_entity = flecs::entity::null();
			if (is_pos_occupied(&flecs_world, cell_goal_location + FVector(0,0, -100), touch_entity))
			{
				return false;
			}
		}

		return true;
	}

	bool can_go_left(flecs::entity shape_entity, TArray<flecs::entity>& touched_entity)
	{
		flecs::world flecs_world = shape_entity.world();
		const shape_t* shape = shape_entity.get<shape_t>();
		AActor* shape_actor = shape_entity.get<flecs::ue::entity_link_t>()->actor;
		const shape_movement_params_t* shape_movement = shape_entity.get<shape_movement_params_t>();

		const grid_t* grid = flecs_world.get<grid_t>();
		const player_t* player = flecs_world.get<player_t>();
		float min_idth = player->player->GetActorLocation().Y - grid->grid_width / 2.0;

		for (AActor* cell_actor: shape->cell_actor)
		{
			FVector relative_offset = shape_actor->GetActorLocation() - cell_actor->GetActorLocation();
			FVector cell_goal_location = shape_movement->goal - relative_offset;
			if (cell_goal_location.Y <= min_idth)
				return false;
				
			round_location(cell_goal_location);
			flecs::entity touch_entity = flecs::entity::null();
			if (is_pos_occupied(&flecs_world, cell_goal_location + FVector(0, -100, 0), touch_entity))
			{
				touched_entity.Add(touch_entity);
				return false;
			}
		}

		return true;
	}

	bool can_go_right(flecs::entity shape_entity, TArray<flecs::entity>& touched_entity)
	{
		flecs::world flecs_world = shape_entity.world();
		const shape_t* shape = shape_entity.get<shape_t>();
		AActor* shape_actor = shape_entity.get<flecs::ue::entity_link_t>()->actor;
		const shape_movement_params_t* shape_movement = shape_entity.get<shape_movement_params_t>();

		const grid_t* grid = flecs_world.get<grid_t>();
		const player_t* player = flecs_world.get<player_t>();
		float max_width = player->player->GetActorLocation().Y + grid->grid_width / 2.0;

		for (AActor* cell_actor: shape->cell_actor)
		{
			FVector relative_offset = shape_actor->GetActorLocation() - cell_actor->GetActorLocation();
			FVector cell_goal_location = shape_movement->goal - relative_offset;
			if (cell_goal_location.Y >= max_width - 100)
				return false;
				
			round_location(cell_goal_location);
			flecs::entity touch_entity = flecs::entity::null();
			if (is_pos_occupied(&flecs_world, cell_goal_location + FVector(0, 100, 0), touch_entity))
			{
				touched_entity.Add(touch_entity);
				return false;
			}
		}

		return true;
	}

	bool is_cell_out_of_grid(flecs::entity shape_entity)
	{
		flecs::world flecs_world = shape_entity.world();
		const shape_t* shape = shape_entity.get<shape_t>();
		AActor* shape_actor = shape_entity.get<flecs::ue::entity_link_t>()->actor;
		const shape_movement_params_t* shape_movement = shape_entity.get<shape_movement_params_t>();

		const grid_t* grid = flecs_world.get<grid_t>();
		const player_t* player = flecs_world.get<player_t>();
		float min_height = player->player->GetActorLocation().Z + grid->grid_height / 2.0;

		for (AActor* cell_actor: shape->cell_actor)
		{
			FVector relative_offset = shape_actor->GetActorLocation() - cell_actor->GetActorLocation();
			FVector cell_goal_location = shape_movement->goal - relative_offset;
			if (cell_goal_location.Z >= min_height)
				return true;
		}

		return false;
	}

	FVector find_border_cell(const grid_t* grid, FVector location, FVector offset)
	{
		FVector new_location = location + offset;

		if (const Fgrid_data_t* new_loc = grid->grid.Find(new_location))
		{
			if (new_loc->is_occupied)
			{
				return find_border_cell(grid, new_location, offset);
			}

			return location;
		}

		return  FVector(0,0,0);
	}

	FString get_word(const grid_t* grid, FVector location, FVector offset, TArray<flecs::entity>& word_data)
	{
		FVector new_location = location + offset;

		if (const Fgrid_data_t* new_loc = grid->grid.Find(new_location))
		{
			if (new_loc->is_occupied)
			{
				word_data.Add(new_loc->occupied_entity);
				return new_loc->current_string + get_word(grid, new_location, offset, word_data);
			}

			return "";
		}

		return "";
	}

	FString get_left_to_right_word(const grid_t* grid, FVector location, TArray<flecs::entity>& word_data)
	{
		FVector left_cell_location = find_border_cell(grid, location, FVector(0, -100, 0));
		FString input = grid->grid[left_cell_location].current_string;
		return  input + get_word(grid, left_cell_location, FVector(0, 100, 0), word_data);
	}
	
	FString get_up_to_down_word(const grid_t* grid, FVector location, TArray<flecs::entity>& word_data)
	{
		FVector up_cell_location = find_border_cell(grid, location, FVector(0, 0, 100));
		FString input = grid->grid[up_cell_location].current_string;
		return  input + get_word(grid, up_cell_location, FVector(0, 0, -100), word_data);
	}

	void check_for_words(flecs::entity shape_entity)
	{
		flecs::world flecs_world = shape_entity.world();
		const shape_t* shape = shape_entity.get<shape_t>();
		AActor* shape_actor = shape_entity.get<flecs::ue::entity_link_t>()->actor;
		const shape_movement_params_t* shape_movement = shape_entity.get<shape_movement_params_t>();

		const grid_t* grid = flecs_world.get<grid_t>();
		const player_t* player = flecs_world.get<player_t>();

		TMap<FString, TArray<flecs::entity>> words_found = {};

		for (AActor* cell_actor: shape->cell_actor)
		{
			FVector relative_offset = shape_actor->GetActorLocation() - cell_actor->GetActorLocation();
			FVector cell_goal_location = shape_movement->goal - relative_offset;
			round_location(cell_goal_location);

			TArray<flecs::entity> array_left;
			TArray<flecs::entity> array_down;
			FString word_left = get_left_to_right_word(grid, cell_goal_location, array_left);
			FString word_down = get_up_to_down_word(grid, cell_goal_location, array_down);

			words_found.Add(word_left, array_left);
			words_found.Add(word_down, array_down);
		}
		
		const global_words_t* words = flecs_world.get<tetris::global_words_t>();
		tetris_score_t* score = flecs_world.get_mut<tetris::tetris_score_t>();
		
		for (auto tuple : words_found)
		{
			int add_score = 0.0;
			// If the word exist in our database
			if (auto row = words->character_datatable->FindRow<FWord>(FName(tuple.Key), ""))
			{
				add_score = row->score;
				score->true_score += row->score;

				UE_LOG(LogTemp, Display, TEXT("Word found = %s | Add Score = %d"), *tuple.Key, add_score);
				
				if (const ui_global_t* ui_global = flecs_world.get<ui_global_t>())
				{
					ui_t* ui = ui_global->main_ui.get_mut<ui_t>();
					UTextBlock* add_score_text = ui->add_score.Get();
					add_score_text->SetText(FText::FromString(FString::SanitizeFloat(add_score)));
					FVector2d screen_position = {};
				
					UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ui->add_score.Get());
					APlayerController* player_controller = shape_actor->GetWorld()->GetFirstPlayerController();
					int size_x, size_y;
					player_controller->GetViewportSize(size_x, size_y);
				
					UGameplayStatics::ProjectWorldToScreen(player_controller, shape_actor->GetActorLocation(), screen_position);
					ui->add_score_spring_data.current_position = screen_position - FVector2d(slot->GetAnchors().Maximum.X * size_x, slot->GetAnchors().Maximum.Y * size_y);
				}

				// Simple feedback
				float duration = 0.2;
				int idx = 1;
				for (auto cell_entity : tuple.Value)
				{
					cell_material_intensity_t* mat_intensity = cell_entity.get_mut<tetris::cell_material_intensity_t>();
					mat_intensity->cooldown = duration * idx;
					mat_intensity->elapsed = 0.0;
					mat_intensity->duration = duration;
					idx++;
				}
			}
		}
	}
}
