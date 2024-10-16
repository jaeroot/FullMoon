// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FMPlayerCharacter.h"

#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Combat/FMCombatComponent.h"
#include "GameData/FMGameSingleton.h"
#include "GameData/FMHeroData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/FMInputData.h"
#include "Interface/FMInteractionInterface.h"
#include "Inventory/FMInventoryComponent.h"
#include "Item/FMMainWeapon.h"
#include "Item/FMPickup.h"
#include "ItemData/FMMainWeaponDataAsset.h"
#include "Net/UnrealNetwork.h"
#include "Physics/FMCollision.h"
#include "Skill/FMSkillComponent.h"
#include "Stat/FMStatComponent.h"

AFMPlayerCharacter::AFMPlayerCharacter()
{
	// Set Child Skeletal Mesh
	ChildMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ChildMesh"));
	ChildMesh->SetupAttachment(GetMesh());
	ChildMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ChildMesh->bReceivesDecals = false;

	// Set Movement Component
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;

	// Set Interaction
	bInteract = true;

	// Set Inventory
	InventoryComponent = CreateDefaultSubobject<UFMInventoryComponent>(TEXT("Inventory"));

	// Stat Component
	StatComponent = CreateDefaultSubobject<UFMStatComponent>(TEXT("Stat"));

	// Combat Component
	CombatComponent = CreateDefaultSubobject<UFMCombatComponent>(TEXT("Combat"));
}

void AFMPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Set Child Skeletal Mesh
	SetChildMesh(TEXT("UE5Manny"));

	// Set Parent Skeletal Mesh
	GetMesh()->SetVisibility(false);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	// Set Character Dead Delegate
	StatComponent->OnHPZeroDelegate.AddUObject(this, &AFMPlayerCharacter::SetDead);
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

	// Set Animation End Delegate
	AnimInstance->OnMontageEnded.AddDynamic(this, &AFMPlayerCharacter::FinishedActivateSkill);
}

void AFMPlayerCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFMPlayerCharacter, WeaponAnimLayer);
}

void AFMPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bInteract && IsLocallyControlled())
	{
		TraceForward();
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
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	return Damage;
}

void AFMPlayerCharacter::ToggleMenu()
{
}

void AFMPlayerCharacter::ToggleSetting()
{
}

void AFMPlayerCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMaxSpeed;

	ServerSprintStart();
}

void AFMPlayerCharacter::SprintStop()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;

	ServerSprintStop();
}

void AFMPlayerCharacter::Dash()
{
}

void AFMPlayerCharacter::Attack()
{
	CombatComponent->ActivateSkill(EPlayerSkillCategory::EPSC_Attack);
}

void AFMPlayerCharacter::SpecialSkill()
{
	CombatComponent->ActivateSkill(EPlayerSkillCategory::EPSC_SpecialSkill);
}

void AFMPlayerCharacter::NormalSkill1()
{
	CombatComponent->ActivateSkill(EPlayerSkillCategory::EPSC_NormalAttack1);
}

void AFMPlayerCharacter::NormalSkill2()
{
	CombatComponent->ActivateSkill(EPlayerSkillCategory::EPSC_NormalAttack2);
}

void AFMPlayerCharacter::UltimateSkill()
{
	CombatComponent->ActivateSkill(EPlayerSkillCategory::EPSC_Ultimate);
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
	if (bInteract)
	{
		ServerInteraction();
	}
}

void AFMPlayerCharacter::ServerSprintStart_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMaxSpeed;
}

void AFMPlayerCharacter::ServerSprintStop_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;
}

void AFMPlayerCharacter::SetChildMesh(const FName& Name)
{
	FFMHeroData HeroData = UFMGameSingleton::Get().GetHeroData(Name);
	if (HeroData.HeroMesh.IsPending())
	{
		HeroData.HeroMesh.LoadSynchronous();
	}
	GetChildMesh()->SetSkeletalMesh(HeroData.HeroMesh.Get());
	GetChildMesh()->SetAnimClass(HeroData.HeroAnim);
}

void AFMPlayerCharacter::OnRep_WeaponAnimLayer()
{
	GetMesh()->LinkAnimClassLayers(WeaponAnimLayer);
}

void AFMPlayerCharacter::TraceForward()
{
	FHitResult HitResult;
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + CameraComponent->GetForwardVector() * 500;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	bool bHitResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		FM_CCHANNEL_INTERACTION,
		Params
	);

	if (bHitResult)
	{
		IFMInteractionInterface* HitActor = Cast<IFMInteractionInterface>(HitResult.GetActor());
		FocusedInteractionActor = HitActor;
	}
	else
	{
		FocusedInteractionActor = nullptr;
	}

	// #if ENABLE_DRAW_DEBUG
	// 	FColor Color = bHitResult ? FColor::Green : FColor::Red;
	// 	DrawDebugLine(
	// 		GetWorld(),
	// 		Start,
	// 		End,
	// 		Color,
	// 		false,
	// 		2.0f
	// 	);
	// #endif
}

void AFMPlayerCharacter::ServerInteraction_Implementation()
{
	TraceForward();

	if (FocusedInteractionActor)
	{
		FocusedInteractionActor->Interaction(this);

		UE_LOG(LogFMCharacter, Warning, TEXT("%s"), *Cast<AActor>(FocusedInteractionActor)->GetName());
	}
}

void AFMPlayerCharacter::TakeItem(AFMPickup* Item)
{
	if (IsValid(Item))
	{
		UFMPickupDataAsset* PickupData = Cast<UFMPickupDataAsset>(Item->GetItemData());
		check(PickupData);
		
		int32 Result = InventoryComponent->AddInventoryItem(PickupData, Item->GetCurrentCount());

		if (Result == 0)
		{
			Item->Destroy();
		}
		else
		{
			Item->SetItemCount(Result);
		}
	}
}

void AFMPlayerCharacter::TakeWeapon(AFMWeapon* Weapon)
{
	if (!IsValid(Weapon))
	{
		return;
	}

	// Check Main Weapon
	AFMMainWeapon* MainWeapon = Cast<AFMMainWeapon>(Weapon);
	if (MainWeapon)
	{
		// Unequip OldWeapon
		AFMMainWeapon* OldWeapon = CombatComponent->GetWeapon();
		if (OldWeapon)
		{
			OldWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			OldWeapon->SetEnableCollision(true);
			OldWeapon->SetOwner(nullptr);

			for (auto& AdditionalWeapon : CombatComponent->GetAdditionalWeapons())
			{
				AdditionalWeapon->Destroy();
			}
			CombatComponent->GetAdditionalWeapons().Empty();
		}

		// Equip NewWeapon
		CombatComponent->SetWeapon(MainWeapon);

		UFMMainWeaponDataAsset* MainWeaponData = Cast<UFMMainWeaponDataAsset>(MainWeapon->GetItemData());
		check(MainWeaponData);

		MainWeapon->SetOwner(this);
		MainWeapon->SetEnableCollision(false);
		MainWeapon->AttachToComponent(GetChildMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, MainWeaponData->WeaponSocket);

		for (auto& AdditionalWeapon : MainWeaponData->AdditionalWeapons)
		{
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(AdditionalWeapon.AdditionalMesh, Params);
			if (IsValid(SpawnedActor))
			{
				SpawnedActor->AttachToComponent(GetChildMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, AdditionalWeapon.AdditionalWeaponSocket);
				SpawnedActor->SetOwner(this);
				CombatComponent->GetAdditionalWeapons().Add(SpawnedActor);
			}
		}
		
		// Linke Weapon Anim Layer
		WeaponAnimLayer = MainWeaponData->WeaponAnimLayerClass;
		OnRep_WeaponAnimLayer();
	}
}

void AFMPlayerCharacter::SetDead()
{
}

bool AFMPlayerCharacter::CanActivateSkill(const float SkillCost)
{
	// Check Montage is not playing
	if (AnimInstance->IsAnyMontagePlaying())
	{
		return false;
	}

	// Check Is On Ground
	if (GetCharacterMovement()->IsFalling())
	{
		return false;
	}

	// Stamina Check
	if (StatComponent->GetCurrentStamina() < SkillCost)
	{
		return false;
	}

	return true;
}

void AFMPlayerCharacter::PlaySkillAnimation(UAnimMontage* AnimMontage, const FName& SectionName)
{
	if (IsValid(AnimMontage))
	{
		AnimInstance->Montage_Play(AnimMontage);

		if (!SectionName.IsNone())
		{
			AnimInstance->Montage_JumpToSection(SectionName, AnimMontage);
		}
	}

	if (HasAuthority())
	{
		// Montage_Play to Simulated Proxy
		for (const auto PlayerController : TActorRange<APlayerController>(GetWorld()))
		{
			if (PlayerController && PlayerController != GetController())
			{
				if (!PlayerController->IsLocalController())
				{					
					AFMPlayerCharacter* OtherPlayerCharacter = Cast<AFMPlayerCharacter>(PlayerController->GetPawn());
					if (IsValid(OtherPlayerCharacter))
					{
						OtherPlayerCharacter->ClientPlaySkillAnimation(this, AnimMontage, SectionName);
					}
				}
			}
		}
	}
}

void AFMPlayerCharacter::ApplySkillCost(const float SkillCost)
{
	StatComponent->SubCurrentStamina(SkillCost);
}

void AFMPlayerCharacter::FailedActivateSkill()
{
	for (const auto PlayerController : TActorRange<APlayerController>(GetWorld()))
	{
		if (PlayerController && PlayerController == GetController())
		{
			AFMPlayerCharacter* PlayerCharacter = Cast<AFMPlayerCharacter>(PlayerController->GetPawn());
			if (IsValid(PlayerCharacter))
			{
				PlayerCharacter->ClientFailedActivateSkill(this);
			}

			break;
		}
	}
}

void AFMPlayerCharacter::ClientFailedActivateSkill_Implementation(AFMPlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->CombatComponent->GetSkillComponent()->FailedActivateSkill();
}

void AFMPlayerCharacter::ClientPlaySkillAnimation_Implementation(AFMPlayerCharacter* PlayerCharacter,
                                                                 UAnimMontage* AnimMontage, const FName& SectionName)
{
	PlayerCharacter->PlaySkillAnimation(AnimMontage, SectionName);
}

void AFMPlayerCharacter::FinishedActivateSkill(UAnimMontage* Montage, bool bInterrupted)
{
	if (IsLocallyControlled() || HasAuthority())
	{
		if (CombatComponent->GetSkillComponent()->GetCurrentSkillIndex() != -1)
		{
			CombatComponent->GetSkillComponent()->FinishedActivateSkill();
		}
	}
}
