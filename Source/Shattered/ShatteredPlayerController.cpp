// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShatteredPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "GameFramework/Pawn.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ShatteredCharacter.h"
#include "Engine/World.h"
#include "Engine.h"

AShatteredPlayerController::AShatteredPlayerController()
{
	bAutoManageActiveCameraTarget = false;

	// the player does not start hammering or jumping
	Hammering = false;
	CanHammer = true;
}

void AShatteredPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AShatteredPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AShatteredPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Jump
	InputComponent->BindAction("Jump", IE_Pressed, this, &AShatteredPlayerController::StartJumping);
	InputComponent->BindAction("Jump", IE_Released, this, &AShatteredPlayerController::StopJumping);

	// Hammer
	InputComponent->BindAction("Hammer", IE_Pressed, this, &AShatteredPlayerController::StartHammering);
	InputComponent->BindAction("Hammer", IE_Released, this, &AShatteredPlayerController::StopHammering);

	// Move
	InputComponent->BindAxis("MoveForward", this, &AShatteredPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AShatteredPlayerController::MoveRight);
}

void AShatteredPlayerController::MoveForward(float AxisValue)
{
	FVector Direction = FVector(1.f, 0, 0);
	AShatteredCharacter* ControlledPlayer = Cast<AShatteredCharacter>(GetPawn());
	if (!ControlledPlayer)
	{
		return;
	}
	if (!CanHammer)
	{
		ControlledPlayer->AddMovementInput(Direction, 0.001f * AxisValue);
	}
	else if (ControlledPlayer->GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		ControlledPlayer->AddMovementInput(Direction, 0.3f*AxisValue);
	}
	else
	{
		ControlledPlayer->AddMovementInput(Direction, AxisValue);
	}
}

void AShatteredPlayerController::MoveRight(float AxisValue)
{
	FVector Direction = FVector(0, 1.f, 0);
	AShatteredCharacter* ControlledPlayer = Cast<AShatteredCharacter>(GetPawn());
	if (!ControlledPlayer)
	{
		return;
	}
	if (!CanHammer)
	{
		ControlledPlayer->AddMovementInput(Direction, 0.001f*AxisValue);
	}
	else if (ControlledPlayer->GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		ControlledPlayer->AddMovementInput(Direction, 0.3f * AxisValue);;
	}
	else
	{
		ControlledPlayer->AddMovementInput(Direction, AxisValue);
	}
}

void AShatteredPlayerController::StartJumping()
{
	if (CanHammer)
	{
		AShatteredCharacter* ControlledPlayer = Cast<AShatteredCharacter>(GetPawn());
		if (!ControlledPlayer)
		{
			return;
		}
		ControlledPlayer->JumpMaxHoldTime = 0.2f;
		ControlledPlayer->Jump();
	}
}

void AShatteredPlayerController::StopJumping()
{
	AShatteredCharacter* ControlledPlayer = Cast<AShatteredCharacter>(GetPawn());
	if (!ControlledPlayer)
	{
		return;
	}
	ControlledPlayer->StopJumping();
}

void AShatteredPlayerController::StartHammering()
{
	Hammering = true;
	CanHammer = false;
	AShatteredCharacter* ControlledPlayer = Cast<AShatteredCharacter>(GetPawn());
	if (!ControlledPlayer)
	{
		return;
	}
	ControlledPlayer->StopJumping();
	//ControlledPlayer->GetCharacterMovement()->GravityScale = 0;
	ControlledPlayer->GetMesh()->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));

	FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(TEXT("StartHammering_BP"), ar, NULL, true);
}

void AShatteredPlayerController::StopHammering()
{
	Hammering = false;
	//AShatteredCharacter* ControlledPlayer = Cast<AShatteredCharacter>(GetPawn());
	//ControlledPlayer->GetMesh()->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
	//ControlledPlayer->GetCharacterMovement()->GravityScale = 2.2;
	FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(TEXT("StopHammering_BP"), ar, NULL, true);
}
