// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/FMSkillComponent.h"

#include "Interface/FMCharacterSkillInterface.h"
#include "Net/UnrealNetwork.h"
#include "Skill/FMSkillBase.h"

DEFINE_LOG_CATEGORY(LogFMSkillComponent);

UFMSkillComponent::UFMSkillComponent()
{
	SetIsReplicatedByDefault(true);

	Skills.Init(FFMSkillData(nullptr), static_cast<int32>(EPlayerSkillCategory::EPSC_Max));

	CurrentSkillIndex = -1;
}

void UFMSkillComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

void UFMSkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<IFMCharacterSkillInterface>(GetOwner());
}

void UFMSkillComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UFMSkillComponent, Skills, COND_OwnerOnly);
}

void UFMSkillComponent::ServerActivateSkill_Implementation(const EPlayerSkillCategory SkillCategory)
{
	bool bResult = ActivateSkill(SkillCategory);
	if (bResult)
	{
		// Calculate Skill Cost
		OwnerCharacter->ApplySkillCost(Skills[CurrentSkillIndex].GetSkillData()->SkillCost);

		// Skill CoolDown
		Skills[CurrentSkillIndex].SetCanActivate(false);
	}
}

bool UFMSkillComponent::ActivateSkill(const EPlayerSkillCategory SkillCategory)
{
	// Check Skills Array Range
	const int32 SkillIndex = static_cast<int32>(SkillCategory);
	if (SkillIndex >= Skills.Num())
	{
		UE_LOG(LogFMSkillComponent, Error, TEXT("Invalid Skill Index"));
		
		return false;
	}

	// Check Skill Is nullptr
	if (!Skills[SkillIndex].GetSkillData())
	{
		UE_LOG(LogFMSkillComponent, Error, TEXT("Invalid Skill"));
		
		return false;
	}

	// Check CoolDown
	if (!Skills[SkillIndex].CanActivate())
	{
		UE_LOG(LogFMSkillComponent, Log, TEXT("Skill Is In CoolDown"));

		return false;
	}

	// Check Owner Character IsValid
	if (!OwnerCharacter)
	{
		UE_LOG(LogFMSkillComponent, Error, TEXT("Invalid Character"));
		
		return false;
	}
	
	// Check Skill Condition
	if (!OwnerCharacter->CanActivateSkill(Skills[SkillIndex].GetSkillData()->SkillCost))
	{
		UE_LOG(LogFMSkillComponent, Log, TEXT("Character Can't Activate Skill"));
		
		return false;
	}

	// Activate Skill
	CurrentSkillIndex = SkillIndex;
	OwnerCharacter->PlaySkillAnimation(Skills[SkillIndex].GetSkillData()->SkillMontage);

	return true;
}

void UFMSkillComponent::InitSkills()
{
	for (int Index = 0; Index < Skills.Num(); Index++)
	{
		Skills[Index].SetSkillData(nullptr);
	}
}

void UFMSkillComponent::AddSkill(UFMSkillBase* Skill)
{
	Skills.Add(FFMSkillData(Skill));
}
