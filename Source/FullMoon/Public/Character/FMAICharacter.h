// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/FMAIInterface.h"
#include "Interface/FMWidgetInterface.h"
#include "FMAICharacter.generated.h"

class UFMWidgetComponent;
class UFMSkillComponent;
class UFMStatComponent;

UCLASS()
class FULLMOON_API AFMAICharacter : public ACharacter,
	public IFMAIInterface,
	public IFMWidgetInterface
{
	GENERATED_BODY()

public:
	AFMAICharacter();

	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FString Name = FString("Monster");

// AI Interface
protected:
	virtual float GetAIMaxTraceDistance() override;
	virtual float GetAIDetectDistance() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAIAttackFinished& InOnAttackFinished) override;
	virtual void Attack() override;

protected:
	FAIAttackFinished OnAttackFinished;

// Stat
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	TObjectPtr<UFMStatComponent> StatComponent;

	void SetDead();

// Skill
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
	TObjectPtr<UFMSkillComponent> SkillComponent;

// Widget
protected:
	TObjectPtr<UFMWidgetComponent> WidgetComponent;
	
	virtual void SetupWidget(class UFMUserWidget* InUserWidget) override;
	
};
