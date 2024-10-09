// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "SleepyMill/unreal_utils.h"
#include "SleepyMill/flecs/flecs.h"
#include "SleepyMill/flecs/ue_flecs.h"
#include "SleepyMill/Tetris/Cell/AvailableChar.h"
#include "SleepyMill/Tetris/Cell/cell_type.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("main_camera"));
	camera_component->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(default_mapping_context, 0);
		}
	}

	if (this->character_datatable.LoadSynchronous() != nullptr)
	{
		tetris::global_cell_character_t global_char = {};
		UDataTable* char_data_table = this->character_datatable.Get();
		for (auto it : char_data_table->GetRowMap())
		{
			FAvailableChar* row_value = (FAvailableChar*)(it.Value);
			if (row_value->is_vowel)
				global_char.vowels.Add(row_value->character);
			else
				global_char.consonants.Add(row_value->character);
		}

		flecs::world* flecs_world = flecs::ue::get_world(this);
		flecs_world->set(global_char);
	}
}

void APlayerPawn::on_right_action(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("APlayerPawn::on_right_action"))
}

void APlayerPawn::on_down_action(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("APlayerPawn::on_down_action"))
}

void APlayerPawn::on_left_action(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("APlayerPawn::on_left_action"))
}

void APlayerPawn::on_shift_action(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("APlayerPawn::on_shift_action"))
}

void APlayerPawn::on_rotate_left_action(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("APlayerPawn::on_rotate_left_action"))
	bool is_pressed = Value.Get<bool>();
	if (is_pressed)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FVector spawn_pos = this->GetActorLocation() + this->GetActorForwardVector() * 200;
		FRotator spawn_rot = {};

		AActor* spawned_actor = GetWorld()->SpawnActor(unreal_utils::pick_random(this->shape_list), &spawn_pos, &spawn_rot, SpawnInfo);
	}
}

void APlayerPawn::on_rotate_right_action(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("APlayerPawn::on_rotate_right_action"))
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(right_action, ETriggerEvent::Triggered, this, &APlayerPawn::on_right_action);
		EnhancedInputComponent->BindAction(down_action, ETriggerEvent::Triggered, this, &APlayerPawn::on_down_action);
		EnhancedInputComponent->BindAction(left_action, ETriggerEvent::Triggered, this, &APlayerPawn::on_left_action);
		EnhancedInputComponent->BindAction(shift_action, ETriggerEvent::Triggered, this, &APlayerPawn::on_shift_action);
		EnhancedInputComponent->BindAction(rotate_left_action, ETriggerEvent::Triggered, this, &APlayerPawn::on_rotate_left_action);
		EnhancedInputComponent->BindAction(rotate_right_action, ETriggerEvent::Triggered, this, &APlayerPawn::on_rotate_right_action);
	}
}

