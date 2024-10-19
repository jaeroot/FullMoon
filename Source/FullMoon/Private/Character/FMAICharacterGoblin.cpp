// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FMAICharacterGoblin.h"

AFMAICharacterGoblin::AFMAICharacterGoblin()
{
	HelmetMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HelmetMesh"));
	HelmetMesh->SetupAttachment(GetMesh());
	HelmetMesh->SetLeaderPoseComponent(GetMesh());
	HelmetMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HelmetMesh->bReceivesDecals = false;
	
	BracerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BracerMesh"));
	BracerMesh->SetupAttachment(GetMesh());
	BracerMesh->SetLeaderPoseComponent(GetMesh());
	BracerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BracerMesh->bReceivesDecals = false;

	BodyArmorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyArmorMesh"));
	BodyArmorMesh->SetupAttachment(GetMesh());
	BodyArmorMesh->SetLeaderPoseComponent(GetMesh());
	BodyArmorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BodyArmorMesh->bReceivesDecals = false;

	SkirtMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkirtMesh"));
	SkirtMesh->SetupAttachment(GetMesh());
	SkirtMesh->SetLeaderPoseComponent(GetMesh());
	SkirtMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkirtMesh->bReceivesDecals = false;

	LegArmorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LegArmorMesh"));
	LegArmorMesh->SetupAttachment(GetMesh());
	LegArmorMesh->SetLeaderPoseComponent(GetMesh());
	LegArmorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LegArmorMesh->bReceivesDecals = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh());
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->bReceivesDecals = false;
	
}

void AFMAICharacterGoblin::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	// if (GetAIGoblinDataAsset())
	// {
	// 	HelmetMesh->SetSkeletalMesh(GetAIGoblinDataAsset()->HelmetMesh);
	// 	BracerMesh->SetSkeletalMesh(GetAIGoblinDataAsset()->BracerMesh);
	// 	BodyArmorMesh->SetSkeletalMesh(GetAIGoblinDataAsset()->BodyArmorMesh);
	// 	SkirtMesh->SetSkeletalMesh(GetAIGoblinDataAsset()->SkirtMesh);
	// 	LegArmorMesh->SetSkeletalMesh(GetAIGoblinDataAsset()->LegArmorMesh);
	// 	WeaponMesh->SetSkeletalMesh(GetAIGoblinDataAsset()->WeaponMesh);
	//
	// 	WeaponMesh->SetAnimClass(GetAIGoblinDataAsset()->WeaponAnimClass);
	// }
}

void AFMAICharacterGoblin::SetDead()
{
	Super::SetDead();

	WeaponMesh->GetAnimInstance()->Montage_Play(GetAIGoblinDataAsset()->WeaponDeadMontage);
}

void AFMAICharacterGoblin::ActivateSkill(int32 SkillIndex)
{
	Super::ActivateSkill(SkillIndex);

	WeaponMesh->GetAnimInstance()->Montage_Play(GetAIGoblinDataAsset()->WeaponMontage[SkillIndex]);
}

void AFMAICharacterGoblin::MulticastActivateSkill_Implementation(int32 SkillIndex)
{
	Super::MulticastActivateSkill_Implementation(SkillIndex);
	
	WeaponMesh->GetAnimInstance()->Montage_Play(GetAIGoblinDataAsset()->WeaponMontage[SkillIndex]);
}
