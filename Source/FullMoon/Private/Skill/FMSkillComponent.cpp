// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/FMSkillComponent.h"

#include "EngineUtils.h"
#include "Interface/FMCharacterSkillInterface.h"
#include "Net/UnrealNetwork.h"
#include "Skill/FMSkillBase.h"

DEFINE_LOG_CATEGORY(LogFMSkillComponent);

UFMSkillComponent::UFMSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);

	Skills.Init(FFMSkillData(nullptr), static_cast<int32>(EPlayerSkillCategory::EPSC_Max));
	SkillCoolDowns.Init(0.0f, static_cast<int32>(EPlayerSkillCategory::EPSC_Max));

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

void UFMSkillComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate Skill CoolDown for UI
	for (auto& SkillCoolDown : SkillCoolDowns)
	{
		SkillCoolDown = FMath::Clamp(SkillCoolDown - DeltaTime, 0.0f, SkillCoolDown);
	}
	
	// Calculate Skill CoolDown In Server
	if (GetOwner()->HasAuthority())
	{
		if (!CoolDownList.IsEmpty())
		{
			ElapsedTime += DeltaTime;
			float LastSkillCoolDown = 0.0f;

			while (!CoolDownList.IsEmpty())
			{
				auto Head = CoolDownList.GetHead();
				if (ElapsedTime >= Head->GetValue().SkillCoolDown)
				{
					LastSkillCoolDown = Head->GetValue().SkillCoolDown;
					Skills[Head->GetValue().SkillIndex].SetCanActivate(true);
					CoolDownList.PopHead();
				}
				else
				{
					break;
				}
			}

			if (LastSkillCoolDown != 0.0f)
			{
				LastSkillCoolDown = ElapsedTime;
				ElapsedTime = 0.0f;
				
				auto Iter = CoolDownList.begin();
				while (Iter != CoolDownList.end())
				{
					Iter.GetNode()->GetValue().SkillCoolDown -= LastSkillCoolDown;
				}
			}
		}
	}
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
		CoolDownList.InsertNode(FFMSkillCoolDownData(CurrentSkillIndex, Skills[CurrentSkillIndex].SkillData->SkillCoolTime));
	}
	else if (!GetOwner()->HasAuthority())
	{
		// Server Failed To Activate Skill
		OwnerCharacter->FailedActivateSkill();
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
		UE_LOG(LogTemp, Log, TEXT("Character Can't Activate Skill"));
		
		return false;
	}

	// Activate Skill
	CurrentSkillIndex = SkillIndex;
	SkillCoolDowns[SkillIndex] = Skills[SkillIndex].GetSkillData()->SkillCost;
	OwnerCharacter->PlaySkillAnimation(Skills[SkillIndex].GetSkillData()->SkillMontage);

	return true;
}

void UFMSkillComponent::FinishedActivateSkill()
{
	CurrentSkillIndex = -1;
}

void UFMSkillComponent::FailedActivateSkill()
{
	check(CurrentSkillIndex > 0);
	
	SkillCoolDowns[CurrentSkillIndex] = 0.0f;
	CurrentSkillIndex = -1;
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
