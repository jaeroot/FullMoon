// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_FMDetect.h"

#include "AIController.h"
#include "AI/FMAIData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"
#include "Physics/FMCollision.h"

UBTService_FMDetect::UBTService_FMDetect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
	TraceRadius = 700.0f;
}

void UBTService_FMDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!IsValid(AIPawn))
	{
		return;
	}

	UWorld* World = AIPawn->GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	// Current Location
	FVector CurrentLocation = AIPawn->GetActorLocation();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_CURRENTLOCATION, CurrentLocation);

	// Detect
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(Detect), false, AIPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		CurrentLocation,
		FQuat::Identity,
		FM_CCHANNEL_ENEMYATTACK,
		FCollisionShape::MakeSphere(TraceRadius),
		CollisionQueryParams
	);

	if (bResult)
	{
		for (const auto& OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				DrawDebugSphere(World, CurrentLocation, TraceRadius, 16, FColor::Green, false, 0.2f);

				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	DrawDebugSphere(World, CurrentLocation, TraceRadius, 16, FColor::Red, false, 0.2f);
}
