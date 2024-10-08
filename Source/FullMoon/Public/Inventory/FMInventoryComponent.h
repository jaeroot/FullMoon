// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData/FMPickupDataAsset.h"
#include "FMInventoryComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFMInventory, Warning, All);

USTRUCT(BlueprintType)
struct FFMInventoryItem
{
	GENERATED_BODY()

public:
	FFMInventoryItem()
	: ItemCount(0)
	{
	}

public:
	FORCEINLINE void Clear() { ItemData = nullptr; ItemCount = 0; }

	FORCEINLINE UFMPickupDataAsset* GetItemData() const { return ItemData; }
	FORCEINLINE int32 GetItemCount() const { return ItemCount; }
	FORCEINLINE FName GetItemName() const { return ItemData->ItemName; }

	FORCEINLINE void SetItemData(UFMPickupDataAsset* NewItemData) { ItemData = NewItemData; }

	/** @return Remaining Item Count */ 
	int32 AddItem(int32 NewItemCount)
	{
		if (NewItemCount <= ItemData->MaxCount - ItemCount)
		{
			ItemCount += NewItemCount;

			return 0;
		}
		
		int32 EmptyCount = ItemData->MaxCount - ItemCount;
		ItemCount += EmptyCount;
		NewItemCount -= EmptyCount;

		return NewItemCount;
	}

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	TObjectPtr<UFMPickupDataAsset> ItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	int32 ItemCount;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FULLMOON_API UFMInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFMInventoryComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FORCEINLINE const TArray<FFMInventoryItem>& GetInventory() const { return Inventory; }

	/**
	 *
	 * @param NewItemData ItemData
	 * @param NewItemCount Item Count
	 * @return Remaining Item Count
	 * If return 0, Successfully add All Item
	 */
	int32 AddInventoryItem(UFMPickupDataAsset* NewItemData, int32 NewItemCount);
	void RemoveInventoryItem(int32 SlotNum);
	void SpawnInventoryItem(int32 SlotNum);
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_Inventory, VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<FFMInventoryItem> Inventory;

	const int32 InventoryMaxCount = 20;

	UFUNCTION()
	void OnRep_Inventory();
	
};
