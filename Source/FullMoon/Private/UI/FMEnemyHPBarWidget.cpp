// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FMEnemyHPBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UFMEnemyHPBarWidget::NativeConstruct()
{
	EnemyName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TEXT_Name")));
	
	Super::NativeConstruct();

	FrontProgressBar->SetFillColorAndOpacity(FLinearColor(0.545098f, 0.0f, 0.0f, 1.0f));
	
}

void UFMEnemyHPBarWidget::SetEnemyName(const FString& NewName)
{
	if (EnemyName)
	{
		EnemyName->SetText(FText::FromString(NewName));
	}
}
