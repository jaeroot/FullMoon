// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/FMUserWidget.h"
#include "FMHPBarWidget.generated.h"

class UTimelineComponent;
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FULLMOON_API UFMHPBarWidget : public UFMUserWidget
{
	GENERATED_BODY()

public:
	UFMHPBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHPBar(float NewCurrentHP, float NewMaxHP);
	void UpdateOldHP(float NewHP);

protected:
	UPROPERTY()
	TObjectPtr<UProgressBar> FrontProgressBar;
	
	UPROPERTY()
	TObjectPtr<UProgressBar> BackProgressBar;

	UPROPERTY()
	float CurrentHP = 100.0f;

	UPROPERTY()
	float MaxHP = 100.0f;

	UPROPERTY()
	float OldHP = 100.0f;

	
};
