// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/FMItemBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Physics/FMCollision.h"

AFMItemBase::AFMItemBase()
{
 	// Set Capsule Component
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Capsule->SetCollisionProfileName(FM_CPROFILE_ITEMPHYSICS);
	Capsule->SetSimulatePhysics(true);
	Capsule->SetCapsuleHalfHeight(50.0f);
	Capsule->SetIsReplicated(true);

	// Set Item Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->bReceivesDecals = false;
	Mesh->SetIsReplicated(true);

	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(RootComponent);
	InteractCollision->SetCollisionProfileName(FM_CPROFILE_ITEM);
	InteractCollision->SetSphereRadius(100.0f);

	bReplicates = true;
}

void AFMItemBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFMItemBase, CurrentCount);
}

void AFMItemBase::SetItem(const FName& Name)
{
}

void AFMItemBase::OnRep_CurrentCount()
{
}
