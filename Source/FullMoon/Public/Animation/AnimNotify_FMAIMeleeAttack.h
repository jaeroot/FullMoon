// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FMAIMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UAnimNotify_FMAIMeleeAttack : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_FMAIMeleeAttack();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
