// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData/FMAssetManager.h"
#include "GameData/FMHeroData.h"
#include "ItemData/FMItemBaseDataAsset.h"
#include "FMMainWeaponDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAdditionalWeapon
{
	GENERATED_BODY()

	FAdditionalWeapon()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	FName AdditionalWeaponSocket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSoftObjectPtr<UStaticMesh> AdditionalMesh;
	
};

UCLASS()
class FULLMOON_API UFMMainWeaponDataAsset : public UFMItemBaseDataAsset
{
	GENERATED_BODY()

public:
	UFMMainWeaponDataAsset()
	{
		ItemType = UFMAssetManager::MainWeaponItemType;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat)
	FFMHeroStat WeaponStat;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	FName WeaponSocket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TArray<FAdditionalWeapon> AdditionalWeapons;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TSubclassOf<UAnimInstance> WeaponAnimLayerClass;
	
};
