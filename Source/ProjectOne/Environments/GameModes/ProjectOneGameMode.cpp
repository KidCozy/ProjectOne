// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ProjectOneGameMode.h"
#include "Player/ProjectOneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectOneGameMode::AProjectOneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/ProjectOne.PlayerCharacter'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}