// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FMSkillBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFMSkill, Warning, All);

UCLASS()
class FULLMOON_API UFMSkillBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFMSkillBase();

public:
	virtual void ActivateSkill();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	FName SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	FString SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	float SkillCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill)
	float SkillCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	FSlateBrush SkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<UAnimMontage> SkillMontage;
	
};
