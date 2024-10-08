// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FMCombatComponent.generated.h"


class AFMMainWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FULLMOON_API UFMCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFMCombatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FORCEINLINE AFMMainWeapon* GetWeapon() const { return Weapon; }
	FORCEINLINE void SetWeapon(AFMMainWeapon* NewWeapon) { Weapon = NewWeapon; }
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_Weapon, VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<AFMMainWeapon> Weapon;
	
	UFUNCTION()
	void OnRep_Weapon();
};
