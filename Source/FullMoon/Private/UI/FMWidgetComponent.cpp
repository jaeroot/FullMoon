// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FMWidgetComponent.h"

#include "UI/FMUserWidget.h"

void UFMWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UFMUserWidget* FMUserWidget = Cast<UFMUserWidget>(GetWidget());
	if (FMUserWidget)
	{
		FMUserWidget->SetOwningActor(GetOwner());
	}
}
