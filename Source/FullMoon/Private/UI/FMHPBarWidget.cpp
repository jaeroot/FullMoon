// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FMHPBarWidget.h"

#include "Components/ProgressBar.h"
#include "Interface/FMWidgetInterface.h"

UFMHPBarWidget::UFMHPBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UFMHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FrontProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_Front")));
	
	BackProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_Back")));

	IFMWidgetInterface* WidgetCharacter = Cast<IFMWidgetInterface>(OwningActor);
	if (WidgetCharacter)
	{
		WidgetCharacter->SetupWidget(this);
	}
}

void UFMHPBarWidget::UpdateHPBar(float NewCurrentHP, float NewMaxHP)
{
	CurrentHP = NewCurrentHP;
	MaxHP = NewMaxHP;

	if (FrontProgressBar)
	{
		FrontProgressBar->SetPercent(CurrentHP / MaxHP);
	}
}

void UFMHPBarWidget::UpdateOldHP(float NewHP)
{
	OldHP = NewHP;
	
	if (BackProgressBar)
	{
		BackProgressBar->SetPercent(OldHP / MaxHP);
	}
}
