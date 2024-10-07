// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FMStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FULLMOON_API UFMStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFMStatComponent();

protected:
	virtual void BeginPlay() override;

};
