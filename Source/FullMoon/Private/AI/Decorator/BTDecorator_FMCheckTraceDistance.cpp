// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_FMCheckTraceDistance.h"

#include "AIController.h"
#include "AI/FMAIData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/FMAIInterface.h"

UBTDecorator_FMCheckTraceDistance::UBTDecorator_FMCheckTraceDistance()
{
	NodeName = TEXT("CheckTraceDistance");
}

bool UBTDecorator_FMCheckTraceDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	IFMAIInterface* AIPawn = Cast<IFMAIInterface>(ControllingPawn);
	if (!AIPawn)
	{
		return false;
	}

	// Calculate Distance from BaseLocation
	FVector BaseLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_BASELOCATION);
	FVector CurrentLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_CURRENTLOCATION);
	float Distance = FVector::Distance(BaseLocation, CurrentLocation);
	float MaxDistance = AIPawn->GetAIMaxTraceDistance();

	bResult = (Distance <= MaxDistance);
	
	return bResult;	
}
