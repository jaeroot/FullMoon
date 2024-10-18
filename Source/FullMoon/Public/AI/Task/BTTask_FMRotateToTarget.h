// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FMRotateToTarget.generated.h"

struct FRotateToTargetNodeMemory
{
	float TurnSpeed = 0.0f;
	FRotator TargetRotator = FRotator::ZeroRotator;
};

UCLASS()
class FULLMOON_API UBTTask_FMRotateToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FMRotateToTarget();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	virtual uint16 GetInstanceMemorySize() const override;
};
