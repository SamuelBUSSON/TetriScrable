// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "flecs.h"
#include "Components/ActorComponent.h"
#include "FlecsEntity.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SLEEPYMILL_API UFlecsEntity : public UActorComponent
{
	GENERATED_BODY()

public:
	flecs::entity entity = {};

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type end_play_reason) override;
};
