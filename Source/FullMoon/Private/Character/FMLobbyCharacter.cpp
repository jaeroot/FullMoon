// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FMLobbyCharacter.h"

AFMLobbyCharacter::AFMLobbyCharacter()
{
}

void AFMLobbyCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		FInputModeUIOnly InputModeUIOnly;
		PlayerController->SetInputMode(InputModeUIOnly);
		PlayerController->SetShowMouseCursor(true);
	}
}
