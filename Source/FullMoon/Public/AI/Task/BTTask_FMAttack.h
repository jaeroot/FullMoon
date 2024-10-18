// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FMAttack.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UBTTask_FMAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FMAttack();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
