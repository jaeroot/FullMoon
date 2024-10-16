// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_FMSweepAttack.h"

#include "Interface/FMAnimNotifyInterface.h"

DEFINE_LOG_CATEGORY(LogFMAnimSweepAttack);

UAnimNotifyState_FMSweepAttack::UAnimNotifyState_FMSweepAttack()
{
}

void UAnimNotifyState_FMSweepAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (FirstSocketName == NAME_None || SecondSocketName == NAME_None)
	{
		bError = true;

		return;
	}

	IFMAnimNotifyInterface* OwnerCharacter = Cast<IFMAnimNotifyInterface>(MeshComp->GetOwner());
	if (OwnerCharacter)
	{
		OwnerCharacter->SweepAttack(FirstSocketName, SecondSocketName, Radius, true, false);
		bError = false;
	}
}

void UAnimNotifyState_FMSweepAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (bError)
	{
		return;
	}

	IFMAnimNotifyInterface* OwnerCharacter = Cast<IFMAnimNotifyInterface>(MeshComp->GetOwner());
	if (OwnerCharacter)
	{
		OwnerCharacter->SweepAttack(FirstSocketName, SecondSocketName, Radius, false, false);
	}
}

void UAnimNotifyState_FMSweepAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (bError)
	{
		return;
	}
	
	IFMAnimNotifyInterface* OwnerCharacter = Cast<IFMAnimNotifyInterface>(MeshComp->GetOwner());
	if (OwnerCharacter)
	{
		OwnerCharacter->SweepAttack(FirstSocketName, SecondSocketName, Radius, false, true);
	}
}
