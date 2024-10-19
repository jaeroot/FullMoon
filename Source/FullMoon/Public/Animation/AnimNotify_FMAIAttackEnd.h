// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FMAIAttackEnd.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UAnimNotify_FMAIAttackEnd : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_FMAIAttackEnd();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
