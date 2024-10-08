// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/FMWeapon.h"
#include "FMMainWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API AFMMainWeapon : public AFMWeapon
{
	GENERATED_BODY()

public:
	AFMMainWeapon();

public:
	virtual void Attack() override;
	virtual void SpecialSkill();
	virtual void NormalSkill1();
	virtual void NormalSkill2();
	virtual void UltimateSkill();
	
};
