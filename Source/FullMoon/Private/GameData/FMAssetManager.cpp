// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/FMAssetManager.h"

DEFINE_LOG_CATEGORY(LogFMAssetManager);

const FPrimaryAssetType UFMAssetManager::PickupItemType = TEXT("Pickup");
const FPrimaryAssetType UFMAssetManager::AutoPickupItemType = TEXT("AutoPickup");
const FPrimaryAssetType UFMAssetManager::MainWeaponItemType = TEXT("MainWeapon");
const FPrimaryAssetType UFMAssetManager::SubWeaponItemType = TEXT("SubWeapon");

UFMAssetManager::UFMAssetManager()
{
}

UFMAssetManager& UFMAssetManager::Get()
{
	UFMAssetManager* AssetManager = CastChecked<UFMAssetManager>(GEngine->AssetManager);
	if (::IsValid(AssetManager))
	{
		return *AssetManager;
	}

	UE_LOG(LogFMAssetManager, Error, TEXT("Invalid Asset Manager"));
	return *NewObject<UFMAssetManager>();
}
