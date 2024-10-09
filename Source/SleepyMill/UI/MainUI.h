// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SLEEPYMILL_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* main_score = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* add_score = nullptr;

	UFUNCTION(BlueprintCallable)
	void init_widget(UObject* world_context);
};
