// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMPlayerSkillData.h"
#include "Skill/FMSkillComponent.h"
#include "FMPlayerSkillComponent.generated.h"

class UFMSkillBase;
/**
 * 
 */
UCLASS()
class FULLMOON_API UFMPlayerSkillComponent : public UFMSkillComponent
{
	GENERATED_BODY()

public:
	UFMPlayerSkillComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void ActivateSkill(EPlayerSkillCategory SkillCategory);
	
public:
	FORCEINLINE TArray<TObjectPtr<UFMSkillBase>>& GetAllSkills() { return Skills; }
	FORCEINLINE UFMSkillBase* GetSkill(EPlayerSkillCategory SkillCategory) const { return Skills[static_cast<int32>(SkillCategory)]; }
	FORCEINLINE void SetAllSkills(const TArray<TObjectPtr<UFMSkillBase>>& NewSkills) { ClearSkills(); Skills = NewSkills; };
	FORCEINLINE void ClearSkills() { Skills.Empty(); }

	void InitSkills();
	void AddSkill(UFMSkillBase* Skill);

protected:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	TArray<TObjectPtr<UFMSkillBase>> Skills;

	
};
