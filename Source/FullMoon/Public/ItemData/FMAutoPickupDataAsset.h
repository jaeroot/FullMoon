// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData/FMAssetManager.h"
#include "GameData/FMHeroData.h"
#include "ItemData/FMItemBaseDataAsset.h"
#include "FMAutoPickupDataAsset.generated.h"

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	EPT_Temporary		UMETA(DisplayName = "Temporary Stat"),
	EPT_Permanent		UMETA(DisplayName = "Permanent Stat"),
	EPT_Replenish		UMETA(DisplayName = "Replenish"),

	EPT_MAX				UMETA(Hidden)
};

UCLASS()
class FULLMOON_API UFMAutoPickupDataAsset : public UFMItemBaseDataAsset
{
	GENERATED_BODY()

public:
	UFMAutoPickupDataAsset()
		: PickupType(EPickupType::EPT_Temporary), Duration(0.0f), ReplenishHP(0.0f), ReplenishStamina(0.0f)
	{
		ItemType = UFMAssetManager::AutoPickupItemType;
	}

public:
	UPROPERTY(EditAnywhere, Category = Pickup)
	EPickupType PickupType;

	UPROPERTY(EditAnywhere, Category = BuffStat, Meta = (EditCondition = "PickupType == EPickupType::EPT_Temporary"))
	float Duration;
	
	UPROPERTY(EditAnywhere, Category = BuffStat, Meta = (EditCondition = "PickupType == EPickupType::EPT_Temporary"))
	FFMHeroStat BuffStat;
	
	UPROPERTY(EditAnywhere, Category = AdditionalStat, Meta = (EditCondition = "PickupType == EPickupType::EPT_Permanent"))
	FFMHeroStat AdditionalStat;
	
	UPROPERTY(EditAnywhere, Category = ReplenishStat, Meta = (EditCondition = "PickupType == EPickupType::EPT_Replenish"))
	float ReplenishHP;
	
	UPROPERTY(EditAnywhere, Category = ReplenishStat, Meta = (EditCondition = "PickupType == EPickupType::EPT_Replenish"))
	float ReplenishStamina;
};
