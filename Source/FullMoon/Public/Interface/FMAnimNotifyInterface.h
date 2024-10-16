// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/FMPlayerSkillData.h"
#include "UObject/Interface.h"
#include "FMAnimNotifyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFMAnimNotifyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FULLMOON_API IFMAnimNotifyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Skill Anim Notify
	virtual UParticleSystemComponent* GetParticleSystemComponent() const = 0;
	virtual void SweepAttack(FName FirstSocketName, FName SecondSocketName, float Radius, bool bIsStart, bool bIsEnd) = 0;
	
};
