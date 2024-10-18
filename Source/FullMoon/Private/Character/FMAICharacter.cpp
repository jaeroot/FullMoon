// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FMAICharacter.h"

#include "AI/FMAIController.h"
#include "Components/CapsuleComponent.h"
#include "Physics/FMCollision.h"
#include "Skill/FMSkillComponent.h"
#include "Stat/FMStatComponent.h"
#include "UI/FMEnemyHPBarWidget.h"
#include "UI/FMUserWidget.h"
#include "UI/FMWidgetComponent.h"

AFMAICharacter::AFMAICharacter()
{
	// AI Controller, Possess Setting
	AIControllerClass = AFMAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Capsule Component
	GetCapsuleComponent()->SetCollisionProfileName(FM_CPROFILE_ENEMY);
	GetCapsuleComponent()->SetCapsuleHalfHeight(95.0f);
	GetCapsuleComponent()->SetCapsuleRadius(35.0f);

	// Set Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SkeletalMeshRef(TEXT("/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin"));
	if (SkeletalMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMeshAsset(SkeletalMeshRef.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -95.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->bReceivesDecals = false;

	// Animation
	// static ConstructorHelpers::FClassFinder<UAnimInstance>
	// 	AnimClassRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Goblin/ABP_Goblin.ABP_Goblin_C'"));
	// if (AnimClassRef.Succeeded())
	// {
	// 	GetMesh()->SetAnimClass(AnimClassRef.Class);
	// }

	// Stat Component
	StatComponent = CreateDefaultSubobject<UFMStatComponent>(TEXT("StatComponent"));

	// Skill Component
	SkillComponent = CreateDefaultSubobject<UFMSkillComponent>(TEXT("SkillComponent"));

	// Widget
	WidgetComponent = CreateDefaultSubobject<UFMWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());
	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UFMUserWidget>
		WidgetClassRef(TEXT("/Game/_FullMoon/UI/InGame/LayeredHPBar/WBP_EnemyHPBar.WBP_EnemyHPBar_C"));
	if (WidgetClassRef.Succeeded())
	{
		WidgetComponent->SetWidgetClass(WidgetClassRef.Class);
	}
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(150.0f, 26.0f));
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFMAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StatComponent->OnHPZeroDelegate.AddUObject(this, &AFMAICharacter::SetDead);
}

float AFMAICharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                 class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float Defense = StatComponent->GetTotalStat().Defense;
	float ApplyDamage = FMath::Clamp(DamageAmount - Defense, 1.0f, DamageAmount);

	StatComponent->SubCurrentHP(ApplyDamage);

	return Damage;
}

float AFMAICharacter::GetAIMaxTraceDistance()
{
	return 1000.0f;
}

float AFMAICharacter::GetAIDetectDistance()
{
	return 700.0f;
}

float AFMAICharacter::GetAITurnSpeed()
{
	return 2.0f;
}

void AFMAICharacter::SetAIAttackDelegate(const FAIAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AFMAICharacter::Attack()
{
	
}

void AFMAICharacter::SetDead()
{
	AFMAIController* FMAIController = Cast<AFMAIController>(GetController());
	if (IsValid(FMAIController))
	{
		FMAIController->StopAI();
	}

	
	SetActorEnableCollision(false);
	WidgetComponent->SetHiddenInGame(true);
	// GetMesh()->GetAnimInstance()->Montage_Play(DeadMontage);

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}
	), 3.0f, false);
}

void AFMAICharacter::SetupWidget(class UFMUserWidget* InUserWidget)
{
	UFMEnemyHPBarWidget* HPBarWidget = Cast<UFMEnemyHPBarWidget>(InUserWidget);
	if (IsValid(HPBarWidget))
	{	
		HPBarWidget->SetEnemyName(Name);
		
		HPBarWidget->UpdateHPBar(StatComponent->GetCurrentHP(), StatComponent->GetMaxHP());
		HPBarWidget->UpdateOldHP(StatComponent->GetOldHP());
		
		StatComponent->OnHPChangedDelegate.AddUObject(HPBarWidget, &UFMHPBarWidget::UpdateHPBar);
		StatComponent->OnOldHPChangedDelegate.AddUObject(HPBarWidget, &UFMHPBarWidget::UpdateOldHP);
	}
}
