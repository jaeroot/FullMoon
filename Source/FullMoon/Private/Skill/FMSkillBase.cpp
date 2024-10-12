// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/FMSkillBase.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogFMSkill);

UFMSkillBase::UFMSkillBase()
	: SkillCost(0.0f), SkillCoolTime(0.0f)
{
}

bool UFMSkillBase::ActivateSkill(AActor* Owner)
{
	if (!IsValid(Owner))
	{
		UE_LOG(LogFMSkill, Error, TEXT("Cannot Find Owner"));
		
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(Owner);
	if (!IsValid(Character))
	{
		UE_LOG(LogFMSkill, Error, TEXT("Cannot Find Character"));
		
		return false;
	}
	
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (!IsValid(AnimInstance))
	{
		UE_LOG(LogFMSkill, Error, TEXT("Cannot Find AnimInstance"));
		
		return false;
	}

	if (AnimInstance->IsAnyMontagePlaying() || Character->GetCharacterMovement()->IsFalling())
	{
		return false;
	}

	AnimInstance->Montage_Play(SkillMontage);

	return true;
}
