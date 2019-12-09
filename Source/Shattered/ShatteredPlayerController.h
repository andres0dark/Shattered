// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShatteredPlayerController.generated.h"

UCLASS()
class AShatteredPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShatteredPlayerController();

	//Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Hammering;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanHammer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

private:
	UFUNCTION()
	void MoveForward(float AxisValue);
	UFUNCTION()
	void MoveRight(float AxisValue);
	UFUNCTION()
	void StartJumping();
	UFUNCTION()
	void StopJumping();
	UFUNCTION()
	void StartHammering();
	UFUNCTION()
	void StopHammering();
};
