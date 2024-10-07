// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FMCombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FULLMOON_API UFMCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFMCombatComponent();

protected:
	virtual void BeginPlay() override;

		
};
