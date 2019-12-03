// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShatteredGameMode.h"
#include "ShatteredPlayerController.h"
#include "ShatteredCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShatteredGameMode::AShatteredGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AShatteredPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/PlayerCharacter/ShatteredCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}