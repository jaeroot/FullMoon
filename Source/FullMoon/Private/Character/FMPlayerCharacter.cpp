// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FMPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameData/FMGameSingleton.h"
#include "GameData/FMHeroData.h"
#include "Input/FMInputData.h"

AFMPlayerCharacter::AFMPlayerCharacter()
{
	// Set Child Skeletal Mesh
	ChildMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ChildMesh"));
	ChildMesh->SetupAttachment(GetMesh());
	ChildMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ChildMesh->bReceivesDecals = false;

}

void AFMPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Set Child Skeletal Mesh
	FFMHeroData HeroData = UFMGameSingleton::Get().GetHeroData(TEXT("UE5Manny"));
	if (HeroData.HeroMesh.IsPending())
	{
		HeroData.HeroMesh.LoadSynchronous();
	}
	GetChildMesh()->SetSkeletalMesh(HeroData.HeroMesh.Get());
	GetChildMesh()->SetAnimClass(HeroData.HeroAnim);

	// Set Parent Skeletal Mesh
	GetMesh()->SetVisibility(false);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void AFMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set Enhanced Input
	if (IsLocallyControlled())
	{
		APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add Menu IMC
			const UFMMenuInputData* MenuInputData = GetDefault<UFMMenuInputData>();
			SubSystem->AddMappingContext(MenuInputData->MenuInputMappingContext, 2);
			
			// Add Combat IMC
			const UFMCombatInputData* CombatInputData = GetDefault<UFMCombatInputData>();
			SubSystem->AddMappingContext(CombatInputData->CombatInputMappingContext, 0);
		}

		PlayerController->SetShowMouseCursor(false);
		FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
	}

}

void AFMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	// Bind Menu Input Actions
	const UFMMenuInputData* MenuInputData = GetDefault<UFMMenuInputData>();
	EnhancedInputComponent->BindAction(MenuInputData->MenuAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::ToggleMenu);
	EnhancedInputComponent->BindAction(MenuInputData->SettingAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::ToggleSetting);
	
	// Bind Combat Input Actions
	const UFMCombatInputData* CombatInputData = GetDefault<UFMCombatInputData>();
	EnhancedInputComponent->BindAction(CombatInputData->SprintAction, ETriggerEvent::Started, this, &AFMPlayerCharacter::SprintStart);
	EnhancedInputComponent->BindAction(CombatInputData->SprintAction, ETriggerEvent::Completed, this, &AFMPlayerCharacter::SprintStop);
	EnhancedInputComponent->BindAction(CombatInputData->DashAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::Dash);
	EnhancedInputComponent->BindAction(CombatInputData->AttackAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::Attack);
	EnhancedInputComponent->BindAction(CombatInputData->SpecialSkillAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::SpecialSkill);
	EnhancedInputComponent->BindAction(CombatInputData->NormalSkillAction1, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::NormalSkill1);
	EnhancedInputComponent->BindAction(CombatInputData->NormalSkillAction2, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::NormalSkill2);
	EnhancedInputComponent->BindAction(CombatInputData->UltimateSkillAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::UltimateSkill);
	EnhancedInputComponent->BindAction(CombatInputData->LockAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::ToggleLockOn);
	EnhancedInputComponent->BindAction(CombatInputData->ResurrectAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::Resurrect);
	EnhancedInputComponent->BindAction(CombatInputData->NoEquipAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::NoEquip);
	EnhancedInputComponent->BindAction(CombatInputData->InteractAction, ETriggerEvent::Triggered, this, &AFMPlayerCharacter::Interaction);
}

float AFMPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AFMPlayerCharacter::ToggleMenu()
{
}

void AFMPlayerCharacter::ToggleSetting()
{
}

void AFMPlayerCharacter::SprintStart()
{
}

void AFMPlayerCharacter::SprintStop()
{
}

void AFMPlayerCharacter::Dash()
{
}

void AFMPlayerCharacter::Attack()
{
}

void AFMPlayerCharacter::SpecialSkill()
{
}

void AFMPlayerCharacter::NormalSkill1()
{
}

void AFMPlayerCharacter::NormalSkill2()
{
}

void AFMPlayerCharacter::UltimateSkill()
{
}

void AFMPlayerCharacter::ToggleLockOn()
{
}

void AFMPlayerCharacter::Resurrect()
{
}

void AFMPlayerCharacter::NoEquip()
{
}

void AFMPlayerCharacter::Interaction()
{
}
