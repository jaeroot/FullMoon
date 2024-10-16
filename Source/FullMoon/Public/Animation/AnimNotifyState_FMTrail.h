// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_FMTrail.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFMAnimTrail, Log, All);

UCLASS(meta = (DisplayName = "FMTrail"))
class FULLMOON_API UAnimNotifyState_FMTrail : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_FMTrail();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trail")
	TObjectPtr<UParticleSystem> PSTemplate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trail")
	FName FirstSocketName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trail")
	FName SecondSocketName = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trail")
	TEnumAsByte<enum ETrailWidthMode> WidthScaleMode = ETrailWidthMode_FromCentre;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trail")
	float InWidth = 1.0f;	

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	uint8 bError : 1 = false;
	
};
