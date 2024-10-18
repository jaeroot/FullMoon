// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/FMStatComponent.h"

#include "GameData/FMGameSingleton.h"
#include "Net/UnrealNetwork.h"

UFMStatComponent::UFMStatComponent()
	: CurrentHP(0.0f), MaxHP(0.0f), CurrentStamina(0.0f), MaxStamina(0.0f)
{
	bWantsInitializeComponent = true;

	HPLerpTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("HPLerpTimelineComponent"));
	OldHPCurveCallback.BindUFunction(this, FName("OldHPLerp"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat>
		OldHPCurveRef(TEXT("/Game/_FullMoon/UI/InGame/LayeredHPBar/CurveFloat_OldHP.CurveFloat_OldHP"));
	if (OldHPCurveRef.Succeeded())
	{
		OldHPCurve = OldHPCurveRef.Object;

		HPLerpTimelineComponent->SetLooping(false);
		HPLerpTimelineComponent->AddInterpFloat(OldHPCurve, OldHPCurveCallback);
		HPLerpTimelineComponent->SetTimelineLength(0.5f);
	}
	
	StaminaLerpTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("StaminaLerpTimelineComponent"));
	OldStaminaCurveCallback.BindUFunction(this, FName("OldStaminaLerp"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat>
		OldStaminaCurveRef(TEXT("/Game/_FullMoon/UI/InGame/LayeredHPBar/CurveFloat_OldStamina.CurveFloat_OldStamina"));
	if (OldStaminaCurveRef.Succeeded())
	{
		OldStaminaCurve = OldStaminaCurveRef.Object;

		StaminaLerpTimelineComponent->SetLooping(false);
		StaminaLerpTimelineComponent->AddInterpFloat(OldStaminaCurve, OldStaminaCurveCallback);
		StaminaLerpTimelineComponent->SetTimelineLength(0.3f);
	}

	SetIsReplicatedByDefault(true);
}

void UFMStatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UFMStatComponent, CurrentHP);
	DOREPLIFETIME(UFMStatComponent, MaxHP);
	DOREPLIFETIME(UFMStatComponent, CurrentStamina);
	DOREPLIFETIME(UFMStatComponent, MaxStamina);
	DOREPLIFETIME_CONDITION(UFMStatComponent, PlayerStat, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UFMStatComponent, BuffStat, COND_OwnerOnly);
}

void UFMStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	InitPlayerStat(TEXT("UE4"));

	OnStatChangedDelegate.AddUObject(this, &UFMStatComponent::SetNewMaxStat);

	if (GetOwner()->HasAuthority())
	{
		FTimerHandle StaminaRecoveryTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			StaminaRecoveryTimerHandle,
			this,
			&UFMStatComponent::StaminaRecovery,
			StaminaRecoveryTime,
			true
		);
	}
}

void UFMStatComponent::AddCurrentHP(const float AddHP)
{
	const float PrevHP = CurrentHP;
	CurrentHP = FMath::Clamp(CurrentHP + AddHP, 0.0f, MaxHP);
	
	if (PrevHP != CurrentHP)
	{
		OnHPChangedDelegate.Broadcast(CurrentHP, MaxHP);
		OldHP = CurrentHP;
	}
	
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPZeroDelegate.Broadcast();
	}
}

void UFMStatComponent::SubCurrentHP(const float SubHP)
{
	const float PrevHP = CurrentHP;
	CurrentHP = FMath::Clamp(CurrentHP - SubHP, 0.0f, MaxHP);
	
	if (PrevHP != CurrentHP)
	{
		OnHPChangedDelegate.Broadcast(CurrentHP, MaxHP);
		CalculateOldHP();
	}
	
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPZeroDelegate.Broadcast();
	}
}

void UFMStatComponent::SetCurrentHP(const float NewHP)
{
	const float PrevHP = CurrentHP;
	CurrentHP = FMath::Clamp(NewHP, 0.0f, MaxHP);

	if (PrevHP != CurrentHP)
	{
		OnHPChangedDelegate.Broadcast(CurrentHP, MaxHP);
		CalculateOldHP();
	}
	
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPZeroDelegate.Broadcast();
	}
}

void UFMStatComponent::AddCurrentStamina(const float AddStamina)
{
	const float PrevStamina = CurrentStamina;
	CurrentStamina = FMath::Clamp(CurrentStamina + AddStamina, 0.0f, MaxStamina);
	
	if (PrevStamina != CurrentStamina)
	{
		OnStaminaChangedDelegate.Broadcast(CurrentStamina, MaxStamina);
		OldStamina = CurrentStamina;
	}
}

void UFMStatComponent::SubCurrentStamina(const float SubStamina)
{
	const float PrevStamina = CurrentStamina;
	CurrentStamina = FMath::Clamp(CurrentStamina - SubStamina, 0.0f, MaxStamina);
	
	if (PrevStamina != CurrentStamina)
	{
		OnStaminaChangedDelegate.Broadcast(CurrentStamina, MaxStamina);
		CalculateOldStamina();
	}
}

void UFMStatComponent::SetCurrentStamina(const float NewStamina)
{
	const float PrevStamina = CurrentStamina;
	CurrentStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
	
	if (PrevStamina != CurrentStamina)
	{
		OnStaminaChangedDelegate.Broadcast(CurrentStamina, MaxStamina);
		CalculateOldStamina();
	}
}

void UFMStatComponent::SetNewMaxStat(const FFMHeroStat& InPlayerStat, const FFMHeroStat& InBuffStat)
{
	const float PrevMaxHP = MaxHP;
	const float PrevMaxStamina = MaxStamina;

	MaxHP = GetTotalStat().MaxHP;
	MaxStamina = GetTotalStat().MaxStamina;

	if (PrevMaxHP != MaxHP || PrevMaxStamina != MaxStamina)
	{
		OnHPChangedDelegate.Broadcast(CurrentHP, MaxHP);
		OnStaminaChangedDelegate.Broadcast(CurrentStamina, MaxStamina);
	}
}

void UFMStatComponent::InitPlayerStat(const FName& Name)
{
	FFMHeroData HeroData = UFMGameSingleton::Get().GetHeroData(Name);

	PlayerStat = static_cast<FFMHeroStat>(HeroData);
	
	MaxHP = PlayerStat.MaxHP;
	MaxStamina = PlayerStat.MaxStamina;

	CurrentHP = MaxHP;
	CurrentStamina = MaxStamina;

	OldHP = CurrentHP;
	SavedOldHP = OldHP;

	OldStamina = CurrentStamina;
	SavedOldStamina = OldStamina;
}

void UFMStatComponent::OnRep_CurrentHP()
{
	OnHPChangedDelegate.Broadcast(CurrentHP, MaxHP);
	if (CurrentHP > OldHP)
	{
		OldHP = CurrentHP;
	}
	CalculateOldHP();
}

void UFMStatComponent::OnRep_MaxHP()
{
	OnHPChangedDelegate.Broadcast(CurrentHP, MaxHP);
}

void UFMStatComponent::OnRep_CurrentStamina()
{
	OnStaminaChangedDelegate.Broadcast(CurrentStamina, MaxStamina);
	if (CurrentStamina > OldStamina)
	{
		OldStamina = CurrentStamina;
	}
	CalculateOldStamina();
}

void UFMStatComponent::OnRep_MaxStamina()
{
	OnStaminaChangedDelegate.Broadcast(CurrentStamina, MaxStamina);
}

void UFMStatComponent::OnRep_PlayerStat()
{
	OnStatChangedDelegate.Broadcast(GetPlayerStat(), GetBuffStat());
}

void UFMStatComponent::OnRep_BuffStat()
{
	OnStatChangedDelegate.Broadcast(GetPlayerStat(), GetBuffStat());
}

void UFMStatComponent::StaminaRecovery()
{
	AddCurrentStamina(StaminaRecoveryAmount);
}

void UFMStatComponent::CalculateOldHP()
{
	SavedOldHP = OldHP;
	
	// HP Lerp
	if (HPLerpTimelineComponent->IsPlaying())
	{
		HPLerpTimelineComponent->Stop();
	}

	HPLerpTimelineComponent->PlayFromStart();
}

void UFMStatComponent::OldHPLerp(float Value)
{
	OldHP = FMath::Lerp(SavedOldHP, CurrentHP, Value);

	OnOldHPChangedDelegate.Broadcast(OldHP);
}

void UFMStatComponent::CalculateOldStamina()
{
	SavedOldStamina = OldStamina;
	
	// HP Lerp
	if (StaminaLerpTimelineComponent->IsPlaying())
	{
		StaminaLerpTimelineComponent->Stop();
	}

	StaminaLerpTimelineComponent->PlayFromStart();
}

void UFMStatComponent::OldStaminaLerp(float Value)
{
	OldStamina = FMath::Lerp(SavedOldStamina, CurrentStamina, Value);

	OnOldStaminaChangedDelegate.Broadcast(OldStamina);
}
