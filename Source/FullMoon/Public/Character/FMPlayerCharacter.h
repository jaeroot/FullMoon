// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FMPlayerCharacterBase.h"
#include "Interface/FMCharacterSkillInterface.h"
#include "Interface/FMTakeItemInterface.h"
#include "Interface/FMTakeWeaponInterface.h"
#include "FMPlayerCharacter.generated.h"

class UFMCombatComponent;
class UFMStatComponent;
class IFMInteractionInterface;
class UFMInventoryComponent;

UCLASS()
class FULLMOON_API AFMPlayerCharacter
	: public AFMPlayerCharacterBase,
	  public IFMTakeItemInterface,
	  public IFMTakeWeaponInterface,
	  public IFMCharacterSkillInterface
{
	GENERATED_BODY()

public:
	AFMPlayerCharacter();
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
// Input Actions
protected:
	// Menu Input Action Functions
	void ToggleMenu();
	void ToggleSetting();

	// Combat Input Action Functions
	void SprintStart();
	void SprintStop();
	void Dash();
	void Attack();
	void SpecialSkill();
	void NormalSkill1();
	void NormalSkill2();
	void UltimateSkill();
	void ToggleLockOn();
	void Resurrect();
	void NoEquip();
	void Interaction();

// Movement
protected:
	const float WalkMaxSpeed = 600.0f;
	const float SprintMaxSpeed = 900.0f;
	
	UFUNCTION(Server, Reliable)
	void ServerSprintStart();

	UFUNCTION(Server, Reliable)
	void ServerSprintStop();
	
// Child Mesh
public:
	FORCEINLINE USkeletalMeshComponent* GetChildMesh() const { return ChildMesh; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> ChildMesh;

	void SetChildMesh(const FName& Name);
	
// Linked Anim Layers
protected:
	UPROPERTY(ReplicatedUsing = OnRep_WeaponAnimLayer, VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	TSubclassOf<UAnimInstance> WeaponAnimLayer;

	UFUNCTION()
	void OnRep_WeaponAnimLayer();

// Interaction
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interact)
	uint8 bInteract : 1;

	IFMInteractionInterface* FocusedInteractionActor;

	void TraceForward();

	UFUNCTION(Server, Reliable)
	void ServerInteraction();

	virtual void TakeItem(class AFMPickup* Item) override;
	virtual void TakeWeapon(class AFMWeapon* Weapon) override;

// Inventory Component
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TObjectPtr<UFMInventoryComponent> InventoryComponent;

// Stat Component
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	TObjectPtr<UFMStatComponent> StatComponent;

	void SetDead();

// Combat Component
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	TObjectPtr<UFMCombatComponent> CombatComponent;

	virtual bool CanActivateSkill(const float SkillCost) override;
	virtual void PlaySkillAnimation(UAnimMontage* AnimMontage, const FName& SectionName = FName()) override;
	virtual void ApplySkillCost(const float SkillCost) override;

	UFUNCTION(Client, Unreliable)
	void ClientPlaySkillAnimation(AFMPlayerCharacter* PlayerCharacter, UAnimMontage* AnimMontage, const FName& SectionName = FName());
	
};
