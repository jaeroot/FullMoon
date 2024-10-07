// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FMPlayerCharacterBase.h"
#include "FMPlayerCharacter.generated.h"

UCLASS()
class FULLMOON_API AFMPlayerCharacter : public AFMPlayerCharacterBase
{
	GENERATED_BODY()

public:
	AFMPlayerCharacter();
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
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

// Child Mesh
public:
	FORCEINLINE USkeletalMeshComponent* GetChildMesh() const { return ChildMesh; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> ChildMesh;
	
// Linked Anim Layers
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	TArray<TObjectPtr<UClass>> LinkedAnimLayers;
	
};
