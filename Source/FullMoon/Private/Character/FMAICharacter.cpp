// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FMAICharacter.h"

#include "EngineUtils.h"
#include "AI/FMAIController.h"
#include "AI/FMAIDataAsset.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -95.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->bReceivesDecals = false;

	// Stat Component
	StatComponent = CreateDefaultSubobject<UFMStatComponent>(TEXT("StatComponent"));

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

	if (IsValid(AIDataAsset))
	{
		// Set Name
		Name = AIDataAsset->AIName;

		// // Set Mesh
		// GetMesh()->SetSkeletalMeshAsset(AIDataAsset->Mesh);
		//
		// // Set Animation
		// GetMesh()->SetAnimClass(AIDataAsset->AnimClass);

		// Set Stat
		StatComponent->OnHPZeroDelegate.AddUObject(this, &AFMAICharacter::SetDead);
		StatComponent->SetPlayerStat(AIDataAsset->AIStat);
		StatComponent->SetCurrentHP(StatComponent->GetMaxHP());
		StatComponent->SetOldHP(StatComponent->GetCurrentHP());
		StatComponent->SetCurrentStamina(StatComponent->GetMaxStamina());
		
		MaxTraceDistance = AIDataAsset->MaxTraceDistance;
		DetectDistance = AIDataAsset->DetectDistance;
		TurnSpeed = AIDataAsset->TurnSpeed;
		AttackRange = AIDataAsset->AttackRange;

		// Set Skill
		SkillCount = AIDataAsset->AISkills.Num();
		SkillCoolDown.Init(0.0f, SkillCount);
		for (auto& Skill : AIDataAsset->AISkills)
		{
			int32 CurrentSkillPriority = Skill.SkillPriority;
			SkillPriority.Add(CurrentSkillPriority);
			TotalSkillPriority += CurrentSkillPriority;
		}

	}
}

void AFMAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Calculate Skill CoolDown
	for(int32 Index = 0; Index < SkillCount; Index++)
	{
		if (SkillCoolDown[Index] > 0.0f)
		{
			SkillCoolDown[Index] = FMath::Clamp(SkillCoolDown[Index] - DeltaSeconds, 0.0f, SkillCoolDown[Index]);

			if (SkillCoolDown[Index] == 0.0f)
			{
				SetDefaultSkillPriority(Index);
			}
		}
	}
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
	return MaxTraceDistance;
}

float AFMAICharacter::GetAIDetectDistance()
{
	return DetectDistance;
}

float AFMAICharacter::GetAITurnSpeed()
{
	return TurnSpeed;
}

void AFMAICharacter::SetAIAttackDelegate(const FAIAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AFMAICharacter::Attack()
{
	if (SkillCount == 0)
	{
		OnAttackFinished.ExecuteIfBound();

		return;
	}
	
	// Calculate Skill Priority
	int PriorityIndex = FMath::RandRange(1, TotalSkillPriority);
	int32 ActivateSkillIndex = 0;
	for (int32 Index = 0; Index < SkillCount; Index++)
	{
		if (PriorityIndex <= SkillPriority[Index])
		{
			// Reduce Activate Skill's Priority
			TotalSkillPriority -= SkillPriority[Index];
			SkillPriority[Index] = 0;

			// Check Skill CoolDown
			SkillCoolDown[Index] = AIDataAsset->AISkills[Index].SkillData->SkillCoolTime;
			if (SkillCoolDown[Index] == 0.0f)
			{
				SetDefaultSkillPriority(Index);
			}

			// Save Activate Skill Index
			ActivateSkillIndex = Index;

			break;
		}
	}

	// Update Skill Priority
	for (int32 Index = 0; Index < SkillCount; Index++)
	{
		if (Index != ActivateSkillIndex && SkillCoolDown[Index] == 0.0f)
		{
			AddSkillPriorityWeight(Index);
		}
	}

	// Activate Skill
	ActivateSkill(ActivateSkillIndex);
}

void AFMAICharacter::SetDefaultSkillPriority(int32 Index)
{
	SkillPriority[Index] = AIDataAsset->AISkills[Index].SkillPriority;
	TotalSkillPriority += SkillPriority[Index];
}

void AFMAICharacter::AddSkillPriorityWeight(int32 Index)
{
	int32 SkillPriorityWeight = AIDataAsset->AISkills[Index].SkillPriorityWeight;
	SkillPriority[Index] += SkillPriorityWeight;
	TotalSkillPriority += SkillPriorityWeight;
}

void AFMAICharacter::ActivateSkill(int32 SkillIndex)
{
	MulticastActivateSkill(SkillIndex);

	// need additional features work in Server, perform here
	AIDataAsset->AISkills[SkillIndex].SkillData->ActivateSkill();
}

void AFMAICharacter::MulticastActivateSkill_Implementation(int32 SkillIndex)
{
	// Play Attack Montage
	UAnimMontage* SkillMontage = AIDataAsset->AISkills[SkillIndex].SkillData->SkillMontage;
	GetMesh()->GetAnimInstance()->Montage_Play(SkillMontage);
}

void AFMAICharacter::AttackEnd()
{
	if (HasAuthority())
	{
		OnAttackFinished.ExecuteIfBound();
	}
}

void AFMAICharacter::MeleeAttack()
{
	if (HasAuthority())
	{
		TArray<FHitResult> HitResults;
		FVector StartLocation = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
		FVector EndLocation = StartLocation + GetActorForwardVector() * AttackRange;
		FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

		bool bResult = GetWorld()->SweepMultiByChannel(
			HitResults,
			StartLocation,
			EndLocation,
			FQuat::Identity,
			FM_CCHANNEL_ENEMYATTACK,
			FCollisionShape::MakeSphere(30.0f),
			Params
		);

		if (bResult)
		{
			FDamageEvent DamageEvent;
			for (auto HitResult : HitResults)
			{
				HitResult.GetActor()->TakeDamage(StatComponent->GetTotalStat().AttackDamage, DamageEvent, GetController(), this);
			
				// UGameplayStatics::SpawnEmitterAtLocation(
				// 	GetWorld(),
				// 	MeleeParticle,
				// 	HitResult.ImpactPoint);
			}
		}

		#if ENABLE_DRAW_DEBUG
			FVector CapsuleOrigin = StartLocation + (EndLocation - StartLocation) * 0.5f;
			float CapsuleHalfHeight = AttackRange / 2;
			FColor DrawColor = bResult ? FColor::Green : FColor::Red;
		
			DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, 30.0f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
		
		#endif
	}
}

void AFMAICharacter::MagicAttack()
{
	if (HasAuthority())
	{
		
	}
}

void AFMAICharacter::SetDead()
{
	if (HasAuthority())
	{
		AFMAIController* FMAIController = Cast<AFMAIController>(GetController());
		if (IsValid(FMAIController))
		{
			FMAIController->StopAI();
		}
		
		FTimerHandle DeadTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				Destroy();
			}
		), 5.0f, false);
	}

	GetCharacterMovement()->SetMovementMode(MOVE_None);
	SetActorEnableCollision(false);
	WidgetComponent->SetHiddenInGame(true);
	GetMesh()->GetAnimInstance()->StopAllMontages(0.5f);
	GetMesh()->GetAnimInstance()->Montage_Play(AIDataAsset->DeadMontage);
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
