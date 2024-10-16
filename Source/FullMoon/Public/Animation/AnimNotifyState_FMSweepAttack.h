// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_FMSweepAttack.generated.h"

class IFMAnimNotifyInterface;
DECLARE_LOG_CATEGORY_EXTERN(LogFMAnimSweepAttack, Log, All);

UCLASS(meta = (DisplayName = "FMSweepAttack"))
class FULLMOON_API UAnimNotifyState_FMSweepAttack : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyState_FMSweepAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SweepAttack")
	FName FirstSocketName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SweepAttack")
	FName SecondSocketName = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SweepAttack")
	float Radius = 0.0f;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	uint8 bError : 1 = false;
	
};
