// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FMPlayerCharacter.h"
#include "FMLobbyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API AFMLobbyCharacter : public AFMPlayerCharacter
{
	GENERATED_BODY()

public:
	AFMLobbyCharacter();

	virtual void BeginPlay() override;

	
};
