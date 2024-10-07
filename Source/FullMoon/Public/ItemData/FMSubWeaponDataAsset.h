// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData/FMAssetManager.h"
#include "ItemData/FMItemBaseDataAsset.h"
#include "FMSubWeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UFMSubWeaponDataAsset : public UFMItemBaseDataAsset
{
	GENERATED_BODY()

public:
	UFMSubWeaponDataAsset()
	{
		ItemType = UFMAssetManager::SubWeaponItemType;
	}
};
