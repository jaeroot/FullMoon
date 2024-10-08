// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/FMCombatComponent.h"

#include "Item/FMMainWeapon.h"
#include "Net/UnrealNetwork.h"

UFMCombatComponent::UFMCombatComponent()
{
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

void UFMCombatComponent::OnRep_Weapon()
{
	
}

void UFMCombatComponent::OnRep_AdditionalWeapons()
{
}
