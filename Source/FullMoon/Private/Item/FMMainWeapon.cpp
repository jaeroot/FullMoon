// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/FMMainWeapon.h"

#include "GameFramework/Character.h"
#include "ItemData/FMMainWeaponDataAsset.h"
#include "Skill/FMSkillBase.h"

AFMMainWeapon::AFMMainWeapon()
{
}

void AFMMainWeapon::Attack()
{
	auto a = Cast<UFMMainWeaponDataAsset>(ItemData);
	if (IsValid(a))
	{
		a->AttackSkill;

		auto b = Cast<ACharacter>(GetOwner());
		if (IsValid(b))
		{
			b->GetMesh()->GetAnimInstance()->Montage_Play(a->AttackSkill->SkillMontage);
		}
	}
}

void AFMMainWeapon::SpecialSkill()
{
}

void AFMMainWeapon::NormalSkill1()
{
}

void AFMMainWeapon::NormalSkill2()
{
}

void AFMMainWeapon::UltimateSkill()
{
}
