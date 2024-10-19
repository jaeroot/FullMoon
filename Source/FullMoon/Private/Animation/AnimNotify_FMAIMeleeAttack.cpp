// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_FMAIMeleeAttack.h"

#include "Interface/FMAIAnimNotifyInterface.h"

UAnimNotify_FMAIMeleeAttack::UAnimNotify_FMAIMeleeAttack()
{
}

void UAnimNotify_FMAIMeleeAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	IFMAIAnimNotifyInterface* AIOwner = Cast<IFMAIAnimNotifyInterface>(MeshComp->GetOwner());
	if (AIOwner)
	{
		AIOwner->MeleeAttack();
	}
}
