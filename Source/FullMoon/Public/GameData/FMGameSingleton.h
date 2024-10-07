// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMHeroData.h"
#include "UObject/NoExportTypes.h"
#include "FMGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFMGameSingleton, Warning, All);

UCLASS()
class FULLMOON_API UFMGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UFMGameSingleton();
	static UFMGameSingleton& Get();

// Hero Data
public:
	FFMHeroStat GetHeroStat(const FName& HeroName) const;
	FFMHeroData GetHeroData(const FName& HeroName) const;
	FFMHeroLevelData GetHeroLevelData(const int32 InLevel) const;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> HeroDataTable;

	UPROPERTY()
	TObjectPtr<UDataTable> HeroLevelDataTable;
};
