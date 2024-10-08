// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/FMWeapon.h"

#include "Interface/FMTakeWeaponInterface.h"

AFMWeapon::AFMWeapon()
{
}

void AFMWeapon::Interaction(AActor* OtherActor)
{
	IFMTakeWeaponInterface* TakeWeaponActor = Cast<IFMTakeWeaponInterface>(OtherActor);
	if (TakeWeaponActor)
	{
		TakeWeaponActor->TakeWeapon(this);
	}
}
