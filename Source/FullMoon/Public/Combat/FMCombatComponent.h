// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skill/FMPlayerSkillData.h"
#include "FMCombatComponent.generated.h"


class UFMSkillComponent;
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
	FORCEINLINE void SetWeapon(AFMMainWeapon* NewWeapon);

	FORCEINLINE TArray<TObjectPtr<AActor>>& GetAdditionalWeapons() { return AdditionalWeapons; }

// Weapon
protected:
	UPROPERTY(ReplicatedUsing = OnRep_Weapon, VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<AFMMainWeapon> Weapon;

	UPROPERTY(ReplicatedUsing = OnRep_AdditionalWeapons, VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TArray<TObjectPtr<AActor>> AdditionalWeapons;
	
	UFUNCTION()
	void OnRep_Weapon();

	UFUNCTION()
	void OnRep_AdditionalWeapons();

// Skill
public:
	void ActivateSkill(EPlayerSkillCategory SkillCategory);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	TObjectPtr<UFMSkillComponent> SkillComponent;

	
};
