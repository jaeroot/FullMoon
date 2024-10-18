// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/FMHPBarWidget.h"
#include "FMEnemyHPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UFMEnemyHPBarWidget : public UFMHPBarWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetEnemyName(const FString& NewName);

protected:
	UPROPERTY()
	TObjectPtr<UTextBlock> EnemyName;
	
};
