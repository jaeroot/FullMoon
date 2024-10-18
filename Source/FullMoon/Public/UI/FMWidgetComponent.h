// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FMWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class FULLMOON_API UFMWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void InitWidget() override;
	
};
