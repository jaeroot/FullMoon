// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/FMAIInterface.h"
#include "Interface/FMWidgetInterface.h"
#include "FMAICharacter.generated.h"

class UFMSkillBase;
class UFMAIDataAsset;
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
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName Name = TEXT("Monster");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UFMAIDataAsset> AIDataAsset;

// AI Interface
protected:
	virtual float GetAIMaxTraceDistance() override;
	virtual float GetAIDetectDistance() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAIAttackFinished& InOnAttackFinished) override;
	virtual void Attack() override;

protected:
	FAIAttackFinished OnAttackFinished;

// Skill
protected:
	int32 SkillCount = 0;
	int32 TotalSkillPriority = 0;
	TArray<int32> SkillPriority;
	TArray<float> SkillCoolDown;

	void SetDefaultSkillPriority(int32 Index);
	void AddSkillPriorityWeight(int32 Index);

	void ActivateSkill(int32 SkillIndex);
	
	UFUNCTION(Client, Reliable)
	void ClientActivateSkill(int32 SkillIndex);

// Stat
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	TObjectPtr<UFMStatComponent> StatComponent;

	void SetDead();

// Widget
protected:
	TObjectPtr<UFMWidgetComponent> WidgetComponent;
	
	virtual void SetupWidget(class UFMUserWidget* InUserWidget) override;
	
};
