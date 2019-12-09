// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShatteredCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AShatteredCharacter::AShatteredCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(50.f, 94.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->MaxWalkSpeed = 1100.0f;
	GetCharacterMovement()->MaxAcceleration = 10000.0f;
	GetCharacterMovement()->JumpZVelocity = 800.0f;

	GetCharacterMovement()->BrakingDecelerationFalling = 800.f;
	GetCharacterMovement()->BrakingFriction = 0.5f;
	GetCharacterMovement()->AirControl = 50.f;
	GetCharacterMovement()->GravityScale = 2.2;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

// Called when the game starts or when spawned
void AShatteredCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AShatteredCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
