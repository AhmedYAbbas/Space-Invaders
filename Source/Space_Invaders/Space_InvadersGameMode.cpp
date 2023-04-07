// Copyright Epic Games, Inc. All Rights Reserved.

#include "Space_InvadersGameMode.h"
#include "Space_InvadersCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpace_InvadersGameMode::ASpace_InvadersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
