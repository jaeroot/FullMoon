// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/FMGameMode.h"

#include "Character/FMPlayerCharacter.h"

AFMGameMode::AFMGameMode()
{
	DefaultPawnClass = AFMPlayerCharacter::StaticClass();
	
}
