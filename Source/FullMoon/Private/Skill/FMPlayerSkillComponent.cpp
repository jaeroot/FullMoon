// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/FMPlayerSkillComponent.h"

#include "Net/UnrealNetwork.h"
#include "Skill/FMSkillBase.h"

UFMPlayerSkillComponent::UFMPlayerSkillComponent()
{
	Skills.Init(nullptr, static_cast<int32>(EPlayerSkillCategory::EPSC_Max));
}

void UFMPlayerSkillComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UFMPlayerSkillComponent, Skills, COND_OwnerOnly);
}

void UFMPlayerSkillComponent::ActivateSkill(EPlayerSkillCategory SkillCategory)
{
	// Check Skills Array Range
	int32 SkillIndex = static_cast<int32>(SkillCategory);
	if (SkillIndex >= Skills.Num())
	{
		return;
	}

	// Check Skill Is nullptr
	if (!Skills[SkillIndex])
	{
		return;
	}

	// Check stamina, cooldown
	// SkillComponent->GetSkill(SkillCategory);

	// Activate Skill
	// Need to Move here
	bool bResult = Skills[SkillIndex]->ActivateSkill(GetOwner());
	if (bResult)
	{
		// Set CoolDown, Stamina
	}
}

void UFMPlayerSkillComponent::InitSkills()
{
	for (int index = 0; index < Skills.Num(); index++)
	{
		Skills[index] = nullptr;
	}
}

void UFMPlayerSkillComponent::AddSkill(UFMSkillBase* Skill)
{
	Skills.Add(Skill);
}
