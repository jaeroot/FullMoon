// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_FMAIMagicAttack.h"

#include "Interface/FMAIAnimNotifyInterface.h"

UAnimNotify_FMAIMagicAttack::UAnimNotify_FMAIMagicAttack()
{
}

void UAnimNotify_FMAIMagicAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	IFMAIAnimNotifyInterface* AIOwner = Cast<IFMAIAnimNotifyInterface>(MeshComp->GetOwner());
	if (AIOwner)
	{
		AIOwner->MagicAttack();
	}
	
}
