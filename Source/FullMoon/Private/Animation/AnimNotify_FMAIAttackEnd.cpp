// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_FMAIAttackEnd.h"

#include "Interface/FMAIAnimNotifyInterface.h"

UAnimNotify_FMAIAttackEnd::UAnimNotify_FMAIAttackEnd()
{
}

void UAnimNotify_FMAIAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	IFMAIAnimNotifyInterface* AIOwner = Cast<IFMAIAnimNotifyInterface>(MeshComp->GetOwner());
	if (AIOwner)
	{
		AIOwner->AttackEnd();
	}
	
}
