// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/FMInteractionInterface.h"
#include "Item/FMItemBase.h"
#include "FMWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API AFMWeapon : public AFMItemBase, public IFMInteractionInterface
{
	GENERATED_BODY()

public:
	AFMWeapon();

	virtual void Interaction(AActor* OtherActor) override;
};
