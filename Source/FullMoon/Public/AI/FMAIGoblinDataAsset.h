// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/FMAIDataAsset.h"
#include "FMAIGoblinDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UFMAIGoblinDataAsset : public UFMAIDataAsset
{
	GENERATED_BODY()

public:
	UFMAIGoblinDataAsset()
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMesh> HelmetMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMesh> BracerMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMesh> BodyArmorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMesh> SkirtMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMesh> LegArmorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMesh> WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<UAnimInstance> WeaponAnimClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TArray<TObjectPtr<UAnimMontage>> WeaponMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> WeaponDeadMontage;
};
