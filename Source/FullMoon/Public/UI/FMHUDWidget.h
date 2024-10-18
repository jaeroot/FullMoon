// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FMHUDWidget.generated.h"

class UFMHPBarWidget;
/**
 * 
 */
UCLASS()
class FULLMOON_API UFMHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHPBar(float NewCurrentHP, float NewMaxHP);
	void UpdateOldHP(float NewHP);
	
	void UpdateStaminaBar(float NewCurrentStamina, float NewMaxStamina);
	void UpdateOldStamina(float NewStamina);

protected:
	UPROPERTY()
	TObjectPtr<UFMHPBarWidget> HPBarWidget;
	TObjectPtr<UFMHPBarWidget> StaminaBarWidget;
	
};
