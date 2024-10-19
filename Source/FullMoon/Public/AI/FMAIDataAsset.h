// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameData/FMHeroData.h"
#include "FMAIDataAsset.generated.h"

class UFMSkillBase;

USTRUCT(BlueprintType)
struct FAISkillData
{
	GENERATED_BODY()

public:
	FAISkillData()
		: SkillPriority(1), SkillPriorityWeight(0)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TObjectPtr<UFMSkillBase> SkillData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	int32 SkillPriority;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	int32 SkillPriorityWeight;
	
};

UCLASS()
class FULLMOON_API UFMAIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFMAIDataAsset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIData")
	FName AIName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIData")
	FFMHeroStat AIStat;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Skill")
	TArray<FAISkillData> AISkills;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float MaxTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float DetectDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	float AttackRange;
	
	
};
