// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/FMMainWeapon.h"

#include "GameFramework/Character.h"
#include "ItemData/FMMainWeaponDataAsset.h"
#include "Particles/ParticleSystemComponent.h"
#include "Skill/FMSkillBase.h"

AFMMainWeapon::AFMMainWeapon()
{
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(Mesh);
}
