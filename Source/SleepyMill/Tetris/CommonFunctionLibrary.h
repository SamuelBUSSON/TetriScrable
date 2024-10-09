// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SLEEPYMILL_API UCommonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static float get_current_score(UObject* world_context);
};
