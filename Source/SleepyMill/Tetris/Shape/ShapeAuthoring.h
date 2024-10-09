// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SleepyMill/flecs/FlecsAuthoringComponent.h"
#include "ShapeAuthoring.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SLEEPYMILL_API UShapeAuthoring : public UActorComponent, public IFlecsAuthoringComponent
{
public:
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float damping_ratio = 1.1f;
	
	UPROPERTY(EditAnywhere)
	float frequency = 10.0f;
	
	UPROPERTY(EditAnywhere)
	float angular_damping_ratio = 1.1f;
	
	UPROPERTY(EditAnywhere)
	float angular_frequency = 100.0f;

	virtual void ConvertToEntityComponent(flecs::world* world, flecs::entity& entity) override;
};
