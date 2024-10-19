// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/FMAIGoblinDataAsset.h"
#include "Character/FMAICharacter.h"
#include "FMAICharacterGoblin.generated.h"

class UFMAIGoblinDataAsset;
/**
 * 
 */
UCLASS()
class FULLMOON_API AFMAICharacterGoblin : public AFMAICharacter
{
	GENERATED_BODY()

public:
	AFMAICharacterGoblin();

	virtual void PostInitializeComponents() override;

	FORCEINLINE UFMAIGoblinDataAsset* GetAIGoblinDataAsset() const { return Cast<UFMAIGoblinDataAsset>(AIDataAsset); }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> HelmetMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> BracerMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> BodyArmorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> SkirtMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> LegArmorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

protected:
	virtual void SetDead() override;
	
	virtual void ActivateSkill(int32 SkillIndex) override;
	
	virtual void MulticastActivateSkill_Implementation(int32 SkillIndex) override;
};
