// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FMAIController.h"

#include "AI/FMAIData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AFMAIController::AFMAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBAssetRef(TEXT("/Game/_FullMoon/AI/BB_EnemyAI.BB_EnemyAI"));
	if (BBAssetRef.Succeeded())
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTAssetRef(TEXT("/Game/_FullMoon/AI/BT_EnemyAI.BT_EnemyAI"));
	if (BTAssetRef.Succeeded())
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AFMAIController::RunAI()
{
	UBlackboardComponent* BlackboardComponent = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComponent))
	{
		Blackboard->SetValueAsVector(BBKEY_BASELOCATION, GetPawn()->GetActorLocation());

		bool bResult = RunBehaviorTree(BTAsset);
		ensure(bResult);
	}
}

void AFMAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AFMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
