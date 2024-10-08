// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FMItemBase.generated.h"

class UFMItemBaseDataAsset;
class USphereComponent;
class UCapsuleComponent;

UCLASS()
class FULLMOON_API AFMItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFMItemBase();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	void SetItem(const FName& Name);
	
	FORCEINLINE UFMItemBaseDataAsset* GetItemData() const { return ItemData; }

// Item Mesh
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	TObjectPtr<USphereComponent> InteractCollision;

// Item Data
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	TObjectPtr<UFMItemBaseDataAsset> ItemData;

// Collision
public:
	void SetEnableCollision(bool NewEnableCollision);
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_EnableCollision, VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	uint8 bEnableCollision : 1;

	UFUNCTION()
	void OnRep_EnableCollision();
};
