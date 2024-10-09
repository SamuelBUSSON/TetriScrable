// Fill out your copyright notice in the Description page of Project Settings.


#include "FlecsEntity.h"

#include "FlecsAuthoringComponent.h"
#include "ue_flecs.h"


void UFlecsEntity::BeginPlay()
{
	Super::BeginPlay();

	flecs::world* world = flecs::ue::get_world(GetWorld());
	if (world == nullptr)
	{        
		UE_LOG(LogTemp, Error, TEXT("flecs world is nullptr"));
		return;
	}

	AActor* actor = GetOwner();

	// Create entity + entity link
	entity = world->entity();
	entity.set<flecs::ue::entity_link_t>({actor});

	// Add authoring components
	{
		TArray<UActorComponent*> authoring_components = actor->GetComponentsByInterface(UFlecsAuthoringComponent::StaticClass());
		for (int idx = 0; idx < authoring_components.Num(); ++idx)
		{
			IFlecsAuthoringComponent* interface = Cast<IFlecsAuthoringComponent>(authoring_components[idx]);
			interface->ConvertToEntityComponent(world, entity);
		}
	}
}

void UFlecsEntity::EndPlay(const EEndPlayReason::Type end_play_reason)
{
	flecs::world* world = flecs::ue::get_world(GetWorld());
	if (world == nullptr)
		return;

	entity.destruct();

	Super::EndPlay(end_play_reason);
}