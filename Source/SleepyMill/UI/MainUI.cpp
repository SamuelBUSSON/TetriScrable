// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

#include "ui_type.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"
#include "Components/TextBlock.h"
#include "SleepyMill/flecs/ue_flecs.h"

void UMainUI::init_widget(UObject* world_context)
{
	flecs::world* flecs_world = flecs::ue::get_world(world_context->GetWorld());
	flecs::entity new_entity = flecs_world->entity();

	ui_t ui = {};
	ui.add_score = this->add_score;
	ui.main_score = this->main_score;

	UTextBlock* a = ui.main_score.Get();
	ui.add_score_spring_data.current_position = UWidgetLayoutLibrary::SlotAsCanvasSlot(ui.main_score.Get())->GetPosition(); 
	ui.main_spring_data.current_position = UWidgetLayoutLibrary::SlotAsCanvasSlot(ui.main_score.Get())->GetPosition();
	ui.main_goal = ui.main_spring_data.current_position;
	ui.add_score_goal = ui.main_goal; 

	ui_global_t ui_global = {};
	ui_global.main_ui = new_entity;

	new_entity.set(ui);
	flecs_world->set(ui_global);
}
