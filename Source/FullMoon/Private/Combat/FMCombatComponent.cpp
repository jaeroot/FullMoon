// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/FMCombatComponent.h"

#include "GameFramework/GameStateBase.h"
#include "Item/FMMainWeapon.h"
#include "Net/UnrealNetwork.h"
#include "Skill/FMSkillComponent.h"

UFMCombatComponent::UFMCombatComponent()
{
	SkillComponent = CreateDefaultSubobject<UFMSkillComponent>(TEXT("SkillComponent"));
	
	SetIsReplicatedByDefault(true);
}


void UFMCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UFMCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UFMCombatComponent, Weapon);
	DOREPLIFETIME(UFMCombatComponent, AdditionalWeapons);
}

void UFMCombatComponent::SetWeapon(AFMMainWeapon* NewWeapon)
{
	// Set New Weapon
	Weapon = NewWeapon;

	// Set Skills
	UFMMainWeaponDataAsset* WeaponData = Weapon->GetWeaponData();
	if (IsValid(WeaponData))
	{
		SkillComponent->InitSkills();
		
		for (auto& Skill : WeaponData->Skills)
		{
			SkillComponent->GetAllSkills()[static_cast<int32>(Skill.Key)].SetSkillData(Skill.Value);
		}
	}
}

void UFMCombatComponent::OnRep_Weapon()
{
	
}

void UFMCombatComponent::OnRep_AdditionalWeapons()
{
	
}

void UFMCombatComponent::ActivateSkill(const EPlayerSkillCategory SkillCategory)
{
	// Activate Skill
	bool bResult = true;
	
	if (!GetOwner()->HasAuthority())
	{
		bResult = SkillComponent->ActivateSkill(SkillCategory);
	}

	if (bResult)
	{
		float CurrentTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
		SkillComponent->ServerActivateSkill(SkillCategory, CurrentTime);
	}
}

void UFMCombatComponent::SweepAttack(FName FirstSocketName, FName SecondSocketName, float Radius,
	ECollisionChannel CollisionChannel, bool bIsStart, bool bIsEnd)
{
	const FVector StartLocation = GetWeapon()->GetWeaponSocketLocation(FirstSocketName);
	const FVector EndLocation = GetWeapon()->GetWeaponSocketLocation(SecondSocketName);

	const FTransform FirstSocketLocalTransform = GetWeapon()->GetWeaponSocketLocalTransform(FirstSocketName);
	const FTransform SecondSocketLocalTransform = GetWeapon()->GetWeaponSocketLocalTransform(SecondSocketName);
	
	FName WeaponSocketName = GetWeapon()->GetWeaponData()->WeaponSocket;

	GetSkillComponent()->SweepAttack(StartLocation, EndLocation, Radius, CollisionChannel, bIsStart, bIsEnd
		, FirstSocketLocalTransform, SecondSocketLocalTransform, WeaponSocketName);
}
