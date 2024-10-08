// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData/FMAssetManager.h"
#include "ItemData/FMItemBaseDataAsset.h"
#include "FMPickupDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UFMPickupDataAsset : public UFMItemBaseDataAsset
{
	GENERATED_BODY()

public:
	UFMPickupDataAsset()
		: MaxCount(0)
	{
		ItemType = UFMAssetManager::PickupItemType;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 MaxCount;
};
