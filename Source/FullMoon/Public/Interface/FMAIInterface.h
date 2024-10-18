// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FMAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFMAIInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE(FAIAttackFinished);

class FULLMOON_API IFMAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAIMaxTraceDistance() = 0;
	virtual float GetAIDetectDistance() = 0;
	virtual float GetAITurnSpeed() = 0;

	virtual void SetAIAttackDelegate(const FAIAttackFinished& InOnAttackFinished) = 0;
	virtual void Attack() = 0;
};
