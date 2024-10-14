// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/FMSkillBase.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogFMSkill);

UFMSkillBase::UFMSkillBase()
	: SkillCost(0.0f), SkillCoolTime(0.0f)
{
}

void UFMSkillBase::ActivateSkill()
{
	
}
