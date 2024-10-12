// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/FMWeapon.h"
#include "ItemData/FMMainWeaponDataAsset.h"
#include "FMMainWeapon.generated.h"

class UFMMainWeaponDataAsset;
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
	FORCEINLINE UFMMainWeaponDataAsset* GetWeaponData() const { return Cast<UFMMainWeaponDataAsset>(ItemData); }

	
};
