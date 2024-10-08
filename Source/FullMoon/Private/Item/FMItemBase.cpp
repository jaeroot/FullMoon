// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/FMItemBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Physics/FMCollision.h"

AFMItemBase::AFMItemBase()
{
	// Set Item Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName(FM_CPROFILE_ITEMPHYSICS);
	Mesh->SetSimulatePhysics(true);
	Mesh->bReceivesDecals = false;
	Mesh->SetIsReplicated(true);
	
	// Set Interact Collision
	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(RootComponent);
	InteractCollision->SetCollisionProfileName(FM_CPROFILE_ITEM);
	InteractCollision->SetSphereRadius(100.0f);

	// Set Collision
	bEnableCollision = true;

	bReplicates = true;
}

void AFMItemBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFMItemBase, bEnableCollision);
}

void AFMItemBase::SetItem(const FName& Name)
{
}

void AFMItemBase::SetEnableCollision(bool NewEnableCollision)
{
	bEnableCollision = NewEnableCollision;
	
	OnRep_EnableCollision();
}

void AFMItemBase::OnRep_EnableCollision()
{
	if (bEnableCollision)
	{
		Mesh->SetSimulatePhysics(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InteractCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		Mesh->SetSimulatePhysics(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
