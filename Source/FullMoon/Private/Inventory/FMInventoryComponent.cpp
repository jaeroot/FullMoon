// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/FMInventoryComponent.h"

#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogFMInventory);

UFMInventoryComponent::UFMInventoryComponent()
{
	Inventory.Init(FFMInventoryItem(), InventoryMaxCount);

	SetIsReplicatedByDefault(true);
}

void UFMInventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UFMInventoryComponent, Inventory, COND_OwnerOnly);
}

int32 UFMInventoryComponent::AddInventoryItem(UFMItemBaseDataAsset* NewItemData, int32 NewItemCount)
{
	for (auto& Item : Inventory)
	{
		// ItemData doesn't exist and Inventory slot is empty
		if (Item.ItemData == nullptr)
		{
			Item.ItemData = NewItemData;
		}

		// ItemData exist in Inventory
		if (Item.GetItemName() == NewItemData->ItemName)
		{
			NewItemCount = Item.AddItem(NewItemCount);

			// Add Item Succeed
			if (NewItemCount == 0)
			{
				break;
			}
		}
	}

	return NewItemCount;
}

void UFMInventoryComponent::RemoveInventoryItem(int32 SlotNum)
{
	Inventory[SlotNum].Clear();	
}

void UFMInventoryComponent::SpawnInventoryItem(int32 SlotNum)
{
	RemoveInventoryItem(SlotNum);

	// Spawn Item
	
}

void UFMInventoryComponent::OnRep_Inventory()
{
	UE_LOG(LogFMInventory, Warning, TEXT("OnRep_Inventory"));
}
