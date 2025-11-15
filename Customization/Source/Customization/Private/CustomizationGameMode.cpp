// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomizationGameMode.h"
#include "CustomizationCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACustomizationGameMode::ACustomizationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
