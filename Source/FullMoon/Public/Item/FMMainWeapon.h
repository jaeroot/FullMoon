// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/FMWeapon.h"
#include "ItemData/FMMainWeaponDataAsset.h"
#include "FMMainWeapon.generated.h"

class UFMMainWeaponDataAsset;
/**
 * 
 */
UCLASS()
class FULLMOON_API AFMMainWeapon : public AFMWeapon
{
	GENERATED_BODY()

public:
	AFMMainWeapon();

public:
	FORCEINLINE UFMMainWeaponDataAsset* GetWeaponData() const { return Cast<UFMMainWeaponDataAsset>(ItemData); }

	FORCEINLINE UParticleSystemComponent* GetParticleSystemComponent() const { return ParticleSystemComponent; }

	FORCEINLINE FVector GetWeaponSocketLocation(const FName& InSocketName) const { return Mesh->GetSocketLocation(InSocketName); }
	FORCEINLINE FTransform GetWeaponSocketLocalTransform(const FName& InSocketName) const { return Mesh->GetSocketTransform(InSocketName, RTS_Actor); }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particle")
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;
	
};
