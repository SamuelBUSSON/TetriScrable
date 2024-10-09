// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "SleepyMill/unreal_utils.h"
#include "SleepyMill/flecs/flecs.h"
#include "SleepyMill/flecs/ue_flecs.h"
#include "SleepyMill/Tetris/grid_utils.h"
#include "SleepyMill/Tetris/tetris_type.h"
#include "SleepyMill/Tetris/Cell/AvailableChar.h"
#include "SleepyMill/Tetris/Cell/cell_type.h"
#include "SleepyMill/Tetris/Shape/shape_type.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("main_camera"));
	camera_component->SetupAttachment(GetRootComponent());
	camera_component->ProjectionMode = ECameraProjectionMode::Orthographic;
	camera_component->OrthoWidth = this->camera_width;
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
	
	flecs::world* flecs_world = flecs::ue::get_world(this);

	tetris::player_t player;
	player.player = this;
	flecs_world->set(player);

	// Current shape setup
	tetris::current_shape_t current_shape = {};
	flecs_world->set(current_shape);

	// Score setup
	tetris::tetris_score_t score = {};
	score.damping_ratio = this->score_damping;
	score.frequency = this->score_frequency;
	flecs_world->set(score);

	// Convert to meter
	this->grid_height *= 100;
	this->grid_width *= 100;
	
	// Setup grid data
	tetris::grid_t grid = {};
	grid.grid_height = this->grid_height;
	grid.grid_width = this->grid_width;
	FVector player_loc =  this->GetActorLocation();
	for (int x = -this->grid_width / 2; x < this->grid_width / 2; x += 100)
	{
		for (int y = -this->grid_height / 2; y < this->grid_height / 2; y += 100)
		{
			bool is_x_odd = x / 100 % 2 == 0;
			bool is_y_odd = y / 100 % 2 == 0;
			TSubclassOf<AActor> actor_to_spawm = grid_checker_a;
			if ((is_x_odd && !is_y_odd) || is_y_odd && !is_x_odd)
				actor_to_spawm = grid_checker_b;
			
			FVector position = {};
			position.X = 0;
			position.Y = player_loc.Y + x;
			position.Z = player_loc.Z + y;

			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			FVector spawn_pos = position + this->GetActorForwardVector() * 5000;
			spawn_pos.Y = FMath::RoundToInt(spawn_pos.Y);
			spawn_pos.Z = FMath::RoundToInt(spawn_pos.Z);
			FRotator spawn_rot = FRotator(0, 0, 0);

			this->GetWorld()->SpawnActor(actor_to_spawm, &spawn_pos, &spawn_rot, SpawnInfo);			

			Fgrid_data_t data = {};
			grid.grid.Add(position, data);
		}
	}

	flecs_world->set(grid);

	// Setup game data
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

		flecs_world->set(global_char);
	}
	
	if (this->words_datatable.LoadSynchronous() != nullptr)
	{
		tetris::global_words_t words_list = {};
		words_list.character_datatable = this->words_datatable; 
		flecs_world->set(words_list);
	}
	
}

void move_feedback(TArray<flecs::entity> contact_entities)
{
	for (auto contact_entity : contact_entities)
	{
		tetris::cell_scale_t* cell_scale = contact_entity.get_mut<tetris::cell_scale_t>();
		cell_scale->spring_data.current_velocity += 20;
	}
}


void APlayerPawn::on_right_action(const FInputActionValue& Value)
{
	bool is_pressed = Value.Get<bool>();
	if (is_pressed)
	{
		flecs::world* flecs_world = flecs::ue::get_world(this);
		tetris::current_shape_t* current_shape = flecs_world->get_mut<tetris::current_shape_t>();
		if (!current_shape->can_move)
			return;

		TArray<flecs::entity> contact_entities;
		if (!tetris::can_go_right(current_shape->shape_entity, contact_entities))
		{
			move_feedback(contact_entities);	
			return;
		}
		
		tetris::shape_movement_params_t* movement_params = current_shape->shape_entity.get_mut<tetris::shape_movement_params_t>();
		movement_params->goal += this->GetActorRightVector() * 100;
	}
}

void APlayerPawn::on_down_action(const FInputActionValue& Value)
{
	bool is_pressed = Value.Get<bool>();
	if (is_pressed)
	{
		flecs::world* flecs_world = flecs::ue::get_world(this);
		tetris::current_shape_t* current_shape = flecs_world->get_mut<tetris::current_shape_t>();
		if (!current_shape->can_move)
			return;
		
		if (!tetris::can_go_below(current_shape->shape_entity))
		{
			if (is_shift_pressed)				
				current_shape->can_move = false;
			return;
		}
		
		tetris::shape_movement_params_t* movement_params = current_shape->shape_entity.get_mut<tetris::shape_movement_params_t>();
		movement_params->goal -= this->GetActorUpVector() * 100;
	}
}

void APlayerPawn::on_left_action(const FInputActionValue& Value)
{
	bool is_pressed = Value.Get<bool>();
	if (is_pressed)
	{
		flecs::world* flecs_world = flecs::ue::get_world(this);
		tetris::current_shape_t* current_shape = flecs_world->get_mut<tetris::current_shape_t>();
		if (!current_shape->can_move)
			return;

		TArray<flecs::entity> contact_entities;
		if (!tetris::can_go_left(current_shape->shape_entity, contact_entities))
		{
			move_feedback(contact_entities);
			return;
		}

		tetris::shape_movement_params_t* movement_params = current_shape->shape_entity.get_mut<tetris::shape_movement_params_t>();
		movement_params->goal -= this->GetActorRightVector() * 100;
	}
}

void APlayerPawn::on_shift_action(const FInputActionValue& Value)
{
	bool is_pressed = Value.Get<bool>();
	is_shift_pressed = is_pressed; 
}

void APlayerPawn::on_rotate_left_action(const FInputActionValue& Value)
{
	bool is_pressed = Value.Get<bool>();
	if (is_pressed)
	{
		flecs::world* flecs_world = flecs::ue::get_world(this);
		tetris::current_shape_t* current_shape = flecs_world->get_mut<tetris::current_shape_t>();
		if (!current_shape->can_move)
			return;

		current_shape->shape_actor->AddActorLocalRotation(FRotator(-90, 0, 0));
	}
}

void APlayerPawn::on_rotate_right_action(const FInputActionValue& Value)
{
	bool is_pressed = Value.Get<bool>();
	if (is_pressed)
	{
		flecs::world* flecs_world = flecs::ue::get_world(this);
		tetris::current_shape_t* current_shape = flecs_world->get_mut<tetris::current_shape_t>();
		if (!current_shape->can_move)
			return;

		current_shape->shape_actor->AddActorLocalRotation(FRotator(90, 0, 0));
	}
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

