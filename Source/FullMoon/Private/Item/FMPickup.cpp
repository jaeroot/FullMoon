// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/FMPickup.h"

#include "Interface/FMTakeItemInterface.h"
#include "Net/UnrealNetwork.h"

AFMPickup::AFMPickup()
{
}

void AFMPickup::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFMPickup, CurrentCount);
}

void AFMPickup::Interaction(AActor* OtherActor)
{
	IFMTakeItemInterface* TakeItemActor = Cast<IFMTakeItemInterface>(OtherActor);
	if (TakeItemActor)
	{
		TakeItemActor->TakeItem(this);
	}
}

void AFMPickup::OnRep_CurrentCount()
{
}
