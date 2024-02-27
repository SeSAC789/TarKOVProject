// Copyright Epic Games, Inc. All Rights Reserved.

#include "TarKOVProjectGameMode.h"
#include "TarKOVProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATarKOVProjectGameMode::ATarKOVProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
