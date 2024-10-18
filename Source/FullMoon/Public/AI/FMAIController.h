// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FMAIController.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API AFMAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFMAIController();

public:
	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	TObjectPtr<UBlackboardData> BBAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	TObjectPtr<UBehaviorTree> BTAsset;
	
};
