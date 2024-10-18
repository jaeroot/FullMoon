// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FMHUDWidget.h"

#include "Interface/FMHUDInterface.h"
#include "UI/FMHPBarWidget.h"

void UFMHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBarWidget = Cast<UFMHPBarWidget>(GetWidgetFromName(TEXT("WBP_HPBarWidget")));
	StaminaBarWidget = Cast<UFMHPBarWidget>(GetWidgetFromName(TEXT("WBP_StaminaBarWidget")));

	IFMHUDInterface* HUDPawn = Cast<IFMHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}
	
}

void UFMHUDWidget::UpdateHPBar(float NewCurrentHP, float NewMaxHP)
{
	HPBarWidget->UpdateHPBar(NewCurrentHP, NewMaxHP);
}

void UFMHUDWidget::UpdateOldHP(float NewHP)
{
	HPBarWidget->UpdateOldHP(NewHP);
}

void UFMHUDWidget::UpdateStaminaBar(float NewCurrentStamina, float NewMaxStamina)
{
	StaminaBarWidget->UpdateHPBar(NewCurrentStamina, NewMaxStamina);
}

void UFMHUDWidget::UpdateOldStamina(float NewStamina)
{
	StaminaBarWidget->UpdateOldHP(NewStamina);
}
