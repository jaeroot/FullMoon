// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FMItemBaseDataAsset.generated.h"

class AFMItemBase;

UCLASS()
class FULLMOON_API UFMItemBaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFMItemBaseDataAsset();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 PurchasePrice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 SellingPrice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FSlateBrush ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	TSubclassOf<AFMItemBase> ItemClass;
};
