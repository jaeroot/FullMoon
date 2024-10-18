// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BTDecorator_FMCheckTraceDistance.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UBTDecorator_FMCheckTraceDistance : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_FMCheckTraceDistance();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
