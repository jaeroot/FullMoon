// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FMAIMagicAttack.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UAnimNotify_FMAIMagicAttack : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_FMAIMagicAttack();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
