// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/FMAIAnimNotifyInterface.h"
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
	public IFMWidgetInterface,
	public IFMAIAnimNotifyInterface
{
	GENERATED_BODY()

public:
	AFMAICharacter();

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	FORCEINLINE UFMAIDataAsset* GetAIData() const { return AIDataAsset; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName Name = TEXT("Monster");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UFMAIDataAsset> AIDataAsset;

	float MaxTraceDistance = 0.0f;
	float DetectDistance = 0.0f;
	float TurnSpeed = 0.0f;
	float AttackRange = 150.0f;

// AI Interface
protected:
	virtual float GetAIMaxTraceDistance() override;
	virtual float GetAIDetectDistance() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAIAttackFinished& InOnAttackFinished) override;
	virtual void Attack() override;

protected:
	FAIAttackFinished OnAttackFinished;

// AI Debug
public:
	void AIDebugActivateSkill(UFMSkillBase* SkillData);
	void RunBehaviorTree() const;
	void StopBehaviorTree() const;
	bool IsBehaviorTreeRunning() const;
	
// Skill
protected:
	int32 SkillCount = 0;
	int32 TotalSkillPriority = 0;
	TArray<int32> SkillPriority;
	TArray<float> SkillCoolDown;

	void SetDefaultSkillPriority(int32 Index);
	void AddSkillPriorityWeight(int32 Index);

	virtual void ActivateSkill(int32 SkillIndex);
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastActivateSkill(int32 SkillIndex);

	virtual void AttackEnd() override;
	virtual void MeleeAttack() override;
	virtual void MagicAttack() override;

// Stat
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	TObjectPtr<UFMStatComponent> StatComponent;

	virtual void SetDead();

// Widget
protected:
	TObjectPtr<UFMWidgetComponent> WidgetComponent;
	
	virtual void SetupWidget(class UFMUserWidget* InUserWidget) override;
	
};
