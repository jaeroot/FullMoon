// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_FMTrail.h"

#include "Interface/FMAnimNotifyInterface.h"
#include "Particles/ParticleSystemComponent.h"

DEFINE_LOG_CATEGORY(LogFMAnimTrail);

UAnimNotifyState_FMTrail::UAnimNotifyState_FMTrail()
{
}

void UAnimNotifyState_FMTrail::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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
		UParticleSystemComponent* ParticleSystemComponent = OwnerCharacter->GetParticleSystemComponent();

		if (IsValid(ParticleSystemComponent))
		{
			ParticleSystemComponent->SetTemplate(PSTemplate);
			ParticleSystemComponent->BeginTrails(FirstSocketName, SecondSocketName, WidthScaleMode, InWidth);
			
			bError = false;
		}
	}
}

void UAnimNotifyState_FMTrail::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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
		UParticleSystemComponent* ParticleSystemComponent = OwnerCharacter->GetParticleSystemComponent();

		if (IsValid(ParticleSystemComponent))
		{
			ParticleSystemComponent->EndTrails();
		}
	}
}
