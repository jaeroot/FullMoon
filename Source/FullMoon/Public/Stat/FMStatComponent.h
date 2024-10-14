// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/FMHeroData.h"
#include "FMStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, float /*CurrentHP*/, float /*MaxHP*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedDelegate, float /*CurrentStamina*/, float /*MaxStamina*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FFMHeroStat& /*PlayerStat*/, const FFMHeroStat& /*BuffStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FULLMOON_API UFMStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFMStatComponent();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void InitializeComponent() override;
	
public:
	FOnHPZeroDelegate OnHPZeroDelegate;
	FOnHPChangedDelegate OnHPChangedDelegate;
	FOnStaminaChangedDelegate OnStaminaChangedDelegate;
	FOnStatChangedDelegate OnStatChangedDelegate;

public:
	FORCEINLINE float GetCurrentHP() const { return CurrentHP; }
	FORCEINLINE float GetMaxHP() const { return MaxHP; }
	FORCEINLINE float GetCurrentStamina() const { return CurrentStamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE const FFMHeroStat& GetPlayerStat() const { return PlayerStat; }
	FORCEINLINE const FFMHeroStat& GetBuffStat() const { return BuffStat; }
	FORCEINLINE FFMHeroStat GetTotalStat() const { return PlayerStat + BuffStat; }

	void AddCurrentHP(const float AddHP);
	void SubCurrentHP(const float SubHP);
	void SetCurrentHP(const float NewHP);
	
	void AddCurrentStamina(const float AddStamina);
	void SubCurrentStamina(const float SubStamina);
	void SetCurrentStamina(const float NewStamina);

	FORCEINLINE void AddPlayerStat(const FFMHeroStat& InAddPlayerStat) { PlayerStat = PlayerStat + InAddPlayerStat; OnStatChangedDelegate.Broadcast(GetPlayerStat(), GetBuffStat()); }
	FORCEINLINE void SubPlayerStat(const FFMHeroStat& InSubPlayerStat) { PlayerStat = PlayerStat + InSubPlayerStat; OnStatChangedDelegate.Broadcast(GetPlayerStat(), GetBuffStat()); }
	FORCEINLINE void SetPlayerStat(const FFMHeroStat& InPlayerStat) { PlayerStat = InPlayerStat; OnStatChangedDelegate.Broadcast(GetPlayerStat(), GetBuffStat()); }

	FORCEINLINE void AddBuffStat(const FFMHeroStat& InAddBuffStat) { BuffStat = BuffStat + InAddBuffStat; OnStatChangedDelegate.Broadcast(GetPlayerStat(), GetBuffStat()); }
	FORCEINLINE void SubBuffStat(const FFMHeroStat& InSubBuffStat) { BuffStat = BuffStat + InSubBuffStat; OnStatChangedDelegate.Broadcast(GetPlayerStat(), GetBuffStat()); }
	FORCEINLINE void SetBuffStat(const FFMHeroStat& InBuffStat) { BuffStat = InBuffStat; OnStatChangedDelegate.Broadcast(GetPlayerStat(), GetBuffStat()); }

	void SetNewMaxStat(const FFMHeroStat& InPlayerStat, const FFMHeroStat& InBuffStat);
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHP, Transient, VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	float CurrentHP;
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxHP, VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	float MaxHP;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentStamina, Transient, VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	float CurrentStamina;

	UPROPERTY(ReplicatedUsing = OnRep_MaxStamina, VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	float MaxStamina;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerStat, Transient, VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	FFMHeroStat PlayerStat;

	UPROPERTY(ReplicatedUsing = OnRep_BuffStat, Transient, VisibleAnywhere, BlueprintReadOnly, Category = Stat)
	FFMHeroStat BuffStat;

protected:
	void InitPlayerStat(const FName& Name);
	
	UFUNCTION()
	void OnRep_CurrentHP();
	
	UFUNCTION()
	void OnRep_MaxHP();
	
	UFUNCTION()
	void OnRep_CurrentStamina();
	
	UFUNCTION()
	void OnRep_MaxStamina();
	
	UFUNCTION()
	void OnRep_PlayerStat();
	
	UFUNCTION()
	void OnRep_BuffStat();

protected:
	const float StaminaRecoveryAmount = 0.5f;
	const float StaminaRecoveryTime = 0.1f;

	UFUNCTION()
	void StaminaRecovery();
	
};
