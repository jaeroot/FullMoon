// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FMCharacterSkillInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFMCharacterSkillInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FULLMOON_API IFMCharacterSkillInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool CanActivateSkill(const float SkillCost) = 0;
	virtual void PlaySkillAnimation(UAnimMontage* AnimMontage, const FName& SectionName = FName()) = 0;
	virtual void ApplySkillCost(const float SkillCost) = 0;
};
