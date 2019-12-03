// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShatteredCharacter.generated.h"

UCLASS(Blueprintable)
class AShatteredCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShatteredCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

