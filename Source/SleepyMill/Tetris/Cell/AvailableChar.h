// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "SleepyMill/flecs/flecs.h"
#include "AvailableChar.generated.h"

USTRUCT()
struct FAvailableChar : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString character = FString("");
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool is_vowel = false;
};

USTRUCT()
struct FWord : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString word = FString("");
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int score = 0;
};

USTRUCT()
struct Fgrid_data_t
{
	GENERATED_BODY()
	
	bool is_occupied = false;
	TSoftObjectPtr<AActor> occupied_actor = nullptr;
	flecs::entity occupied_entity;
	FString current_string = FString("");
};

USTRUCT()
struct FWord_Data
{
	GENERATED_BODY()
	
	FString word = FString();
	TArray<flecs::entity> cell_entity;
	
	friend uint32 GetTypeHash(const FWord_Data& PlayerInfo)
	{
		return GetTypeHash(PlayerInfo.word);
	}
	
	friend bool operator==(const FWord_Data& A, const FWord_Data& B)
	{
		if (A.word != B.word)
			return false;

		for (flecs::entity c_a : A.cell_entity)
		{
			for (flecs::entity c_b : B.cell_entity)
			{
				if (c_b == c_a)
					return true;
			}
		}
		
		return false;
	}
};