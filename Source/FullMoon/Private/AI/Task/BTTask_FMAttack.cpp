// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_FMAttack.h"

#include "AIController.h"
#include "Interface/FMAIInterface.h"

UBTTask_FMAttack::UBTTask_FMAttack()
{
	NodeName = TEXT("Attack");
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_FMAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(ControllingPawn))
	{
		return EBTNodeResult::Failed;
	}

	IFMAIInterface* AIPawn = Cast<IFMAIInterface>(ControllingPawn);
	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAIAttackFinished OnAttackFinished;
	OnAttackFinished.BindLambda(
		[&]
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	AIPawn->SetAIAttackDelegate(OnAttackFinished);
	AIPawn->Attack();

	return EBTNodeResult::InProgress;
}
