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
	cell.plane = this->plane.GetComponent(this->GetOwner());
	cell.text_render->SetText(FText::FromString(cell.current_cell_text));

	tetris::cell_scale_t scale = {};
	scale.damping_ratio = scale_damping_ratio;
	scale.frequency = scale_frequency;
	scale.goal = 1.0;

	tetris::cell_material_intensity_t mat_intensity;
	mat_intensity.goal = 1.0;

	entity.set(cell);
	entity.set(mat_intensity);
	entity.set(scale);
}
