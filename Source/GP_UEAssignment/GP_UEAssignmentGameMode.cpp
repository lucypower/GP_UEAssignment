// Copyright Epic Games, Inc. All Rights Reserved.

#include "GP_UEAssignmentGameMode.h"
#include "GP_UEAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGP_UEAssignmentGameMode::AGP_UEAssignmentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
