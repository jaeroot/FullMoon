// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "FMAssetManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFMAssetManager, Error, All);

UCLASS()
class FULLMOON_API UFMAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UFMAssetManager();
	
	static UFMAssetManager& Get();

public:
	static const FPrimaryAssetType PickupItemType;
	static const FPrimaryAssetType AutoPickupItemType;
	static const FPrimaryAssetType MainWeaponItemType;
	static const FPrimaryAssetType SubWeaponItemType;
};
