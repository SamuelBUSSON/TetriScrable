#include "ui_system.h"

#include "ui_type.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "SleepyMill/spring_utils.h"

void ui::update_game_ui(flecs::iter it, ui_t* ui_a)
{
	float dt = it.delta_time();
	for (int idx : it)
	{
		ui_t& ui = ui_a[idx];

		spring_utils::calc_damped_spring_motion_params(ui.main_spring_params, dt, 10, 0.8);
		spring_utils::calc_damped_spring_motion_params(ui.add_score_spring_params, dt, 10, 0.8);

		spring_utils::compute_spring_goal_vector(ui.add_score_goal, ui.add_score_spring_data, ui.add_score_spring_params);
		spring_utils::compute_spring_goal_vector(ui.main_goal, ui.main_spring_data, ui.main_spring_params);

		UCanvasPanelSlot* main_slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ui.main_score.Get());
		UCanvasPanelSlot* add_score_slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ui.add_score.Get());
		
		main_slot->SetPosition(ui.main_spring_data.current_position);
		add_score_slot->SetPosition(ui.add_score_spring_data.current_position);

		float dist = (ui.main_spring_data.current_position - ui.add_score_spring_data.current_position).Length();
		if (dist <= 10)
		{
			ui.main_spring_data.current_velocity += ui.add_score_spring_data.current_velocity * 4.0;
			ui.add_score->SetText(FText::FromString(""));
		}
	}
}
