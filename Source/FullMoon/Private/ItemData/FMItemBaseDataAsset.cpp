// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/FMItemBaseDataAsset.h"

UFMItemBaseDataAsset::UFMItemBaseDataAsset()
	: MaxCount(0), PurchasePrice(0), SellingPrice(0)
{
}

FPrimaryAssetId UFMItemBaseDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}