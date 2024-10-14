// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMPlayerSkillData.h"
#include "Components/ActorComponent.h"
#include "FMSkillComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFMSkillComponent, Error, All);

class UFMSkillBase;
class IFMCharacterSkillInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FULLMOON_API UFMSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFMSkillComponent();

	virtual void InitializeComponent() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	TObjectPtr<IFMCharacterSkillInterface> OwnerCharacter;

public:
	UFUNCTION(Server, Reliable)
	void ServerActivateSkill(const EPlayerSkillCategory SkillCategory);
	
	bool ActivateSkill(const EPlayerSkillCategory SkillCategory);
	
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

	/**
	 * Used to check whether a skill is enabled.
	 * if CurrentSkillIndex == -1, no skills are active.
	 */
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	int32 CurrentSkillIndex = -1;

};
