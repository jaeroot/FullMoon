// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/FMInteractionInterface.h"
#include "Item/FMItemBase.h"
#include "FMPickup.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API AFMPickup : public AFMItemBase, public IFMInteractionInterface
{
	GENERATED_BODY()

public:
	AFMPickup();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Interaction(AActor* OtherActor) override;

public:
	FORCEINLINE int32 GetCurrentCount() const { return CurrentCount; }
	FORCEINLINE void SetItemCount(int32 NewItemCount) { CurrentCount = NewItemCount; }
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentCount, EditAnywhere, Category = Item)
	int32 CurrentCount = 1;

	UFUNCTION()
	void OnRep_CurrentCount();
};
