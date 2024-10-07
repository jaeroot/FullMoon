// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/FMGameSingleton.h"

DEFINE_LOG_CATEGORY(LogFMGameSingleton);

UFMGameSingleton::UFMGameSingleton()
{
	// Set Hero Data
	static ConstructorHelpers::FObjectFinder<UDataTable>
		HeroDataRef(TEXT("/Game/_FullMoon/GameData/DT_FMHeroData.DT_FMHeroData"));
	if (HeroDataRef.Succeeded())
	{
		HeroDataTable = HeroDataRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UDataTable>
		HeroLevelDataRef(TEXT("/Game/_FullMoon/GameData/DT_FMHeroLevelData.DT_FMHeroLevelData"));
	if (HeroLevelDataRef.Succeeded())
	{
		HeroLevelDataTable = HeroLevelDataRef.Object;
	}
}

UFMGameSingleton& UFMGameSingleton::Get()
{
	UFMGameSingleton* GameSingleton = CastChecked<UFMGameSingleton>(GEngine->GameSingleton);
	if (IsValid(GameSingleton))
	{
		return *GameSingleton;
	}

	UE_LOG(LogFMGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UFMGameSingleton>();
}

FFMHeroStat UFMGameSingleton::GetHeroStat(const FName& HeroName) const
{
	check(HeroDataTable);
	FFMHeroStat* HeroStat = HeroDataTable->FindRow<FFMHeroStat>(HeroName, TEXT(""));

	return HeroStat ? *HeroStat : FFMHeroStat();
}

FFMHeroData UFMGameSingleton::GetHeroData(const FName& HeroName) const
{
	check(HeroDataTable);
	FFMHeroData* HeroData = HeroDataTable->FindRow<FFMHeroData>(HeroName, TEXT(""));

	return HeroData ? *HeroData : FFMHeroData();
}

FFMHeroLevelData UFMGameSingleton::GetHeroLevelData(const int32 InLevel) const
{
	check(HeroLevelDataTable);
	FFMHeroLevelData* HeroLevelData =
		HeroLevelDataTable->FindRow<FFMHeroLevelData>(*FString::Printf(TEXT("%d"), InLevel), TEXT(""));

	return HeroLevelData ? *HeroLevelData : FFMHeroLevelData();
}
