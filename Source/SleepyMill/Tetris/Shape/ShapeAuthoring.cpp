// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeAuthoring.h"

#include "shape_type.h"

void UShapeAuthoring::ConvertToEntityComponent(flecs::world* world, flecs::entity& entity)
{
	tetris::shape_t shape = {};
	tetris::shape_movement_params_t movement_params = {};
	movement_params.frequency = this->frequency;
	movement_params.damping_ratio = this->damping_ratio;
	movement_params.spring_data.current_position = this->GetOwner()->GetActorLocation();
	entity.set(shape);
	entity.set(movement_params);
}
