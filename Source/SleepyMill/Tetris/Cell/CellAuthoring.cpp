// Fill out your copyright notice in the Description page of Project Settings.


#include "CellAuthoring.h"

#include "cell_type.h"
#include "cell_utils.h"
#include "Components/TextRenderComponent.h"

void UCellAuthoring::ConvertToEntityComponent(flecs::world* world, flecs::entity& entity)
{
	tetris::cell_t cell = {};
	cell.current_cell_text = tetris::get_random_character(world, this->vowel_rate);
	cell.text_render = this->text_renderer_reference.GetComponent(this->GetOwner());
	cell.text_render->SetText(FText::FromString(cell.current_cell_text));

	entity.set(cell);
}
