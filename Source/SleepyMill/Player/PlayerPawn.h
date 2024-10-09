// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

class UDataTable;

UCLASS()
class SLEEPYMILL_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Global, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UDataTable> character_datatable = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Global, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AActor>> shape_list;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* camera_component;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* default_mapping_context;
	
	/** Right Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* right_action;
	
	/** Down Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* down_action;
	
	/** Left Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* left_action;
	
	/** Shift Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* shift_action;
	
	/** Shift Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* rotate_left_action;
	
	/** Shift Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* rotate_right_action;

	void on_right_action(const FInputActionValue& Value);
	void on_down_action(const FInputActionValue& Value);
	void on_left_action(const FInputActionValue& Value);
	void on_shift_action(const FInputActionValue& Value);
	void on_rotate_left_action(const FInputActionValue& Value);
	void on_rotate_right_action(const FInputActionValue& Value);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
