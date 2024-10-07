// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FMInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFMInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FULLMOON_API IFMInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interaction(AActor* OtherActor) = 0;
	
};
