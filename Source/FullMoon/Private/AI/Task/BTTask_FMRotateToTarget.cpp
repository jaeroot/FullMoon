// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_FMRotateToTarget.h"

#include "AIController.h"
#include "AI/FMAIData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/FMAIInterface.h"

UBTTask_FMRotateToTarget::UBTTask_FMRotateToTarget()
{
	NodeName = TEXT("RotateToTarget");
	bNotifyTick = true;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_FMRotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(ControllingPawn))
	{
		return EBTNodeResult::Failed;
	}

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (!IsValid(TargetPawn))
	{
		return EBTNodeResult::Failed;
	}

	IFMAIInterface* AIPawn = Cast<IFMAIInterface>(ControllingPawn);
	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector TargetVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();
	TargetVector.Z = 0.0f;
	FRotator TargetRotator = FRotationMatrix::MakeFromX(TargetVector).Rotator();

	FRotateToTargetNodeMemory* MyMemory = CastInstanceNodeMemory<FRotateToTargetNodeMemory>(NodeMemory);
	MyMemory->TurnSpeed = AIPawn->GetAITurnSpeed();
	MyMemory->TargetRotator = TargetRotator;
	
	return EBTNodeResult::InProgress;
}

void UBTTask_FMRotateToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(ControllingPawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		
		return;
	}
	
	FRotateToTargetNodeMemory* MyMemory = CastInstanceNodeMemory<FRotateToTargetNodeMemory>(NodeMemory);
	if (!MyMemory)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		
		return;
	}

	ControllingPawn->SetActorRotation(FMath::RInterpTo(
		ControllingPawn->GetActorRotation(),
		MyMemory->TargetRotator,
		GetWorld()->GetDeltaSeconds(),
		MyMemory->TurnSpeed
	));
	
	if (ControllingPawn->GetActorRotation().Equals(MyMemory->TargetRotator, 10.0f))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_FMRotateToTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

uint16 UBTTask_FMRotateToTarget::GetInstanceMemorySize() const
{
	return sizeof(FRotateToTargetNodeMemory);
}
