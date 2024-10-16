#pragma once

#include "CoreMinimal.h"
#include "FMPlayerSkillData.generated.h"

UENUM(BlueprintType)
enum class EPlayerSkillCategory : uint8
{
	EPSC_Attack				UMETA(DisplayName = "Attack"),
	EPSC_SpecialSkill		UMETA(DisplayName = "SpecialSkill"),
	EPSC_NormalAttack1		UMETA(DisplayName = "NormalAttack1"),
	EPSC_NormalAttack2		UMETA(DisplayName = "NormalAttack2"),
	EPSC_Ultimate			UMETA(DisplayName = "Ultimate"),

	EPSC_Max				UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	EST_SweepAttack			UMETA(DisplayName = "SweepAttack"),
	EST_Overlap				UMETA(DisplayName = "Overlap"),
	EST_Buff				UMETA(DisplayName = "Buff"),

	EST_Max					UMETA(Hidden)
};
