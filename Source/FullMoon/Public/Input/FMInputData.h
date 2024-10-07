// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FMInputData.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class FULLMOON_API UFMMenuInputData : public UObject
{
	GENERATED_BODY()

public:
	UFMMenuInputData();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> MenuInputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MenuAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> SettingAction;
	
};


UCLASS()
class UFMBaseFreeInputData : public UObject
{
	GENERATED_BODY()

public:
	UFMBaseFreeInputData();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> BaseFreeInputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> FreeMoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> FreeLookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;
	
};


UCLASS()
class UFMCombatInputData : public UObject
{
	GENERATED_BODY()

public:
	UFMCombatInputData();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> CombatInputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> DashAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> SpecialSkillAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> NormalSkillAction1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> NormalSkillAction2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> UltimateSkillAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> LockAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ResurrectAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> NoEquipAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> InteractAction;
	
};
