// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SleepyMill/flecs/FlecsAuthoringComponent.h"
#include "CellAuthoring.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SLEEPYMILL_API UCellAuthoring : public UActorComponent, public IFlecsAuthoringComponent
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(UIMin = "0.0", UIMax = "1.0"))
	float vowel_rate = 0.4f;
	
	UPROPERTY(EditAnywhere)
	float scale_damping_ratio = 0.4f;
	
	UPROPERTY(EditAnywhere)
	float scale_frequency = 30.0f;

	UPROPERTY(EditAnywhere)
	FComponentReference text_renderer_reference;

	virtual void ConvertToEntityComponent(flecs::world* world, flecs::entity& entity) override;
};
