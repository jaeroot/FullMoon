// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/FMSkillComponent.h"

#include "EngineUtils.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameStateBase.h"
#include "Interface/FMCharacterSkillInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Skill/FMSkillBase.h"

DEFINE_LOG_CATEGORY(LogFMSkillComponent);

UFMSkillComponent::UFMSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);

	Skills.Init(FFMSkillData(nullptr), static_cast<int32>(EPlayerSkillCategory::EPSC_Max));
	SkillCoolDowns.Init(0.0f, static_cast<int32>(EPlayerSkillCategory::EPSC_Max));

	CurrentSkillIndex = -1;
}

void UFMSkillComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

void UFMSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	SkillOwnerCharacter = Cast<IFMCharacterSkillInterface>(GetOwner());
}

void UFMSkillComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UFMSkillComponent, Skills, COND_OwnerOnly);
}

void UFMSkillComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate Skill CoolDown for UI
	for (auto& SkillCoolDown : SkillCoolDowns)
	{
		SkillCoolDown = FMath::Clamp(SkillCoolDown - DeltaTime, 0.0f, SkillCoolDown);
	}
	
	// Calculate Skill CoolDown In Server
	if (GetOwner()->HasAuthority())
	{
		if (!CoolDownList.IsEmpty())
		{
			ElapsedTime += DeltaTime;
			float LastSkillCoolDown = 0.0f;

			while (!CoolDownList.IsEmpty())
			{
				auto Head = CoolDownList.GetHead();
				if (ElapsedTime >= Head->GetValue().SkillCoolDown)
				{
					LastSkillCoolDown = Head->GetValue().SkillCoolDown;
					Skills[Head->GetValue().SkillIndex].SetCanActivate(true);
					CoolDownList.PopHead();
				}
				else
				{
					break;
				}
			}

			if (LastSkillCoolDown != 0.0f)
			{
				LastSkillCoolDown = ElapsedTime;
				ElapsedTime = 0.0f;
				
				auto Iter = CoolDownList.begin();
				while (Iter != CoolDownList.end())
				{
					Iter.GetNode()->GetValue().SkillCoolDown -= LastSkillCoolDown;
				}
			}
		}
	}
}

void UFMSkillComponent::ServerActivateSkill_Implementation(const EPlayerSkillCategory SkillCategory, const float CurrentTime)
{
	bool bResult = ActivateSkill(SkillCategory);
	if (bResult)
	{
		// Calculate Skill Cost
		SkillOwnerCharacter->ApplySkillCost(Skills[CurrentSkillIndex].GetSkillData()->SkillCost);

		// Skill CoolDown
		if (Skills[CurrentSkillIndex].GetSkillData()->SkillCoolTime > 0.0f)
		{
			Skills[CurrentSkillIndex].SetCanActivate(false);
			CoolDownList.InsertNode(FFMSkillCoolDownData(CurrentSkillIndex, Skills[CurrentSkillIndex].SkillData->SkillCoolTime));
		}

		// Save Attack Start Time to Check Attack Hit IsValid
		AttackStartTime = CurrentTime;
	}
	else if (!GetOwner()->HasAuthority())
	{
		// Server Failed To Activate Skill
		SkillOwnerCharacter->FailedActivateSkill();
	}
}

bool UFMSkillComponent::ActivateSkill(const EPlayerSkillCategory SkillCategory)
{
	// Check Skills Array Range
	const int32 SkillIndex = static_cast<int32>(SkillCategory);
	if (SkillIndex >= Skills.Num())
	{
		UE_LOG(LogFMSkillComponent, Error, TEXT("Invalid Skill Index"));
		
		return false;
	}

	// Check Skill Is nullptr
	if (!Skills[SkillIndex].GetSkillData())
	{
		UE_LOG(LogFMSkillComponent, Error, TEXT("Invalid Skill"));
		
		return false;
	}

	// Check CoolDown
	if (!Skills[SkillIndex].CanActivate())
	{
		UE_LOG(LogFMSkillComponent, Log, TEXT("Skill Is In CoolDown"));

		return false;
	}

	// Check Owner Character IsValid
	if (!SkillOwnerCharacter)
	{
		UE_LOG(LogFMSkillComponent, Error, TEXT("Invalid Character"));
		
		return false;
	}
	
	// Check Skill Condition
	if (!SkillOwnerCharacter->CanActivateSkill(Skills[SkillIndex].GetSkillData()->SkillCost))
	{
		UE_LOG(LogTemp, Log, TEXT("Character Can't Activate Skill"));
		
		return false;
	}

	// Activate Skill
	CurrentSkillIndex = SkillIndex;
	SkillCoolDowns[SkillIndex] = Skills[SkillIndex].GetSkillData()->SkillCoolTime;
	SkillOwnerCharacter->PlaySkillAnimation(Skills[SkillIndex].GetSkillData()->SkillMontage);

	return true;
}

void UFMSkillComponent::FinishedActivateSkill()
{
	CurrentSkillIndex = -1;
}

void UFMSkillComponent::FailedActivateSkill()
{
	check(CurrentSkillIndex > 0);
	
	SkillCoolDowns[CurrentSkillIndex] = 0.0f;
	CurrentSkillIndex = -1;
}

void UFMSkillComponent::InitSkills()
{
	for (int Index = 0; Index < Skills.Num(); Index++)
	{
		Skills[Index].SetSkillData(nullptr);
	}
}

void UFMSkillComponent::AddSkill(UFMSkillBase* Skill)
{
	Skills.Add(FFMSkillData(Skill));
}

void UFMSkillComponent::HitStop(float NewPlayRate, float Duration)
{
	UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
	const float PlayRate = AnimInstance->Montage_GetPlayRate(CurrentMontage);
				
	AnimInstance->Montage_SetPlayRate(CurrentMontage, NewPlayRate);
	
	FTimerHandle Handle;
	TWeakObjectPtr<UAnimInstance> WeakAnimInstance(AnimInstance);
	TWeakObjectPtr<UAnimMontage> WeakCurrentMontage(CurrentMontage);
	GetWorld()->GetTimerManager().SetTimer(
		Handle,
		FTimerDelegate::CreateLambda([WeakAnimInstance, WeakCurrentMontage, PlayRate]
		{
			if (WeakAnimInstance.IsValid() && WeakCurrentMontage.IsValid())
			{
				WeakAnimInstance->Montage_SetPlayRate(WeakCurrentMontage.Get(), PlayRate);
			}
		}),
		Duration,
		false,
		-1
	);
	
}

void UFMSkillComponent::SweepAttack(const FVector& StartLocation, const FVector& EndLocation, float Radius,
	ECollisionChannel CollisionChannel, bool bIsStart, bool bIsEnd,
	const FTransform& FirstSocketLocalTransform, const FTransform& SecondSocketLocalTransform, FName WeaponSocketName)
{
	// Get Current AnimSequence
	UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
	
	float CurrentTime = AnimInstance->Montage_GetPosition(CurrentMontage);
	int32 Section = CurrentMontage->GetSectionIndexFromPosition(CurrentTime);
		
	TArray<UAnimationAsset*> AnimationAssets;
	CurrentMontage->GetAllAnimationSequencesReferred(AnimationAssets);

	UAnimSequence* AnimSequence = Cast<UAnimSequence>(AnimationAssets[Section]);
	if (!IsValid(AnimSequence))
	{
		// Failed to Find Current AnimSequence
		UE_LOG(LogFMSkillComponent, Warning, TEXT("Invalid AnimSequence"));

		return;
	}
	
	// Initialize
	if (bIsStart)
	{
		PrevMeshTransform = OwnerCharacter->GetMesh()->GetBoneTransform(RootBone);
		PrevLocation = (StartLocation + EndLocation) / 2;
		PrevDirection = EndLocation - StartLocation;
		PrevTime = CurrentTime;
		HitResultSet.Empty();
		ParentBones.Empty();

		// Add Parent Bones to ParentBones Array
		FName CurrentBoneName = LeafBone;
		while (CurrentBoneName != RootBone)
		{
			int32 BoneIndex = OwnerCharacter->GetMesh()->GetBoneIndex(CurrentBoneName);
			ParentBones.Add(FFMBoneInfo(CurrentBoneName, BoneIndex));

			CurrentBoneName = OwnerCharacter->GetMesh()->GetParentBone(CurrentBoneName);
		}
		
		SweepCollisionDetection(StartLocation, EndLocation, Radius, CollisionChannel);

		return;
	}

	// Calculate SplitNum. If Distance < Radius and !bIsEnd, Don't perform collision detection.
	float Distance = FVector::Distance(StartLocation, PrevLocation + (PrevDirection / 2));
	int32 SplitNum = FMath::CeilToInt(Distance / (Radius * 2));
	if (!bIsEnd && Distance < Radius)
	{
		return;
	}
	
	// Init Data for Interpolation
	float Duration = CurrentTime - PrevTime;
	FTransform CurrentMeshTransform = OwnerCharacter->GetMesh()->GetBoneTransform(RootBone);
	
	// Split between PrevLocation and CurrentLocation
	for (int32 i = 1; i <= SplitNum; i++)
	{
		// Init Duration Time, Leaf Bone Name
		float DurationTime = PrevTime + Duration * i / SplitNum;

		// Calculate Bone Local Transform from RootBone
		FTransform BoneTransform = FTransform::Identity;
		for (int32 Index = ParentBones.Num() - 1; Index >= 0; Index--)
		{
			// Get Current Bone's Transform at DurationTime
			FTransform CurrentTransform;
			AnimSequence->GetBoneTransform(CurrentTransform, FSkeletonPoseBoneIndex(ParentBones[Index].BoneIndex), DurationTime, true);

			BoneTransform = CurrentTransform * BoneTransform;
		}

		// Weapon Socket Transform
		FTransform WeaponSocketTransform = OwnerCharacter->GetMesh()->GetSocketTransform(WeaponSocketName, RTS_ParentBoneSpace);
		BoneTransform = WeaponSocketTransform * BoneTransform;
		
		// Interp Mesh Transform
		FTransform InterpMeshTransform;
		InterpMeshTransform.SetLocation(FMath::Lerp(PrevMeshTransform.GetLocation(), CurrentMeshTransform.GetLocation(), static_cast<float>(i) / 10));
		InterpMeshTransform.SetRotation(FQuat::Slerp(PrevMeshTransform.GetRotation(), CurrentMeshTransform.GetRotation(), static_cast<float>(i) / 10));
		InterpMeshTransform.SetScale3D(FMath::Lerp(PrevMeshTransform.GetScale3D(), CurrentMeshTransform.GetScale3D(), static_cast<float>(i) / 10));
		BoneTransform = BoneTransform * InterpMeshTransform;

		// Weapon Mesh Socket Transform
		FTransform NewStartLocation = FirstSocketLocalTransform * BoneTransform;
		FTransform NewEndLocation = SecondSocketLocalTransform * BoneTransform;
		
		// Do Interp
		SweepCollisionDetection(NewStartLocation.GetLocation(), NewEndLocation.GetLocation(), Radius, CollisionChannel);
	}

	PrevMeshTransform = CurrentMeshTransform;
	PrevTime = CurrentTime;
}

void UFMSkillComponent::SweepCollisionDetection(const FVector& StartLocation, const FVector& EndLocation, float Radius,
	ECollisionChannel CollisionChannel)
{
	const FVector CenterLocation = (StartLocation + EndLocation) / 2;
	const FVector Direction = EndLocation - StartLocation;
	const float HalfHeight = FVector::Distance(StartLocation, EndLocation) / 2;
	
	// Collision Detection (Capsule Sweep)
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	TArray<FHitResult> HitResults;
	bool bHitResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		PrevLocation,
		CenterLocation,
		FRotationMatrix::MakeFromZ(Direction).ToQuat(),
		CollisionChannel,
		FCollisionShape::MakeCapsule(Radius, HalfHeight),
		Params
	);
	
	bool bDrawDebug = false;
	if (bHitResult)
	{
		// Check First Hit. If true, Hit Stop
		if (HitResultSet.IsEmpty())
		{
			if (OwnerCharacter)
			{
				HitStop(0.03f, 0.07f);
			}
		}

		TArray<FHitResult> RemovedDuplicateHitResults;
		for (auto& HitResult : HitResults)
		{
			// Remove Duplicates
			if (HitResultSet.Contains(HitResult.GetActor()))
			{
				continue;
			}

			// float AttackDamage = 100.0f;
			//
			// HitResult.GetActor()->TakeDamage(AttackDamage, FDamageEvent(), OwnerCharacter->GetController(), OwnerCharacter);

			/*UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				Particle,
				HitResult.ImpactPoint
			);*/

			HitResultSet.Add(HitResult.GetActor());
			RemovedDuplicateHitResults.Add(HitResult);
			bDrawDebug = true;
		}

		// Remove Duplicate Hit Result.
		// If Client Failed to activate skill, Don't Call ServerRPC
		if (RemovedDuplicateHitResults.Num() > 0 && CurrentSkillIndex != -1)
		{
			float CurrentTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
			ServerSweepAttack(RemovedDuplicateHitResults, CurrentTime);
		}
	}

	// Draw Debug
#if ENABLE_DRAW_DEBUG
	FColor Color = bDrawDebug ? FColor::Green : FColor::Red;
	DrawDebugCapsule(
		GetWorld(),
		CenterLocation,
		HalfHeight,
		Radius / 2,
		FRotationMatrix::MakeFromZ(Direction).ToQuat(),
		Color,
		false,
		2.0f
	);
	DrawDebugCapsule(
		GetWorld(),
		PrevLocation,
		HalfHeight,
		Radius / 2,
		FRotationMatrix::MakeFromZ(Direction).ToQuat(),
		Color,
		false,
		2.0f
	);

	DrawDebugLine(
		GetWorld(),
		PrevLocation - (Direction / 2),
		StartLocation,
		Color,
		false,
		2.0f
		);
	
	DrawDebugLine(
		GetWorld(),
		PrevLocation + (Direction / 2),
		EndLocation,
		Color,
		false,
		2.0f
	);
#endif
	
	PrevLocation = CenterLocation;
	PrevDirection = Direction;
}

void UFMSkillComponent::ServerSweepAttack_Implementation(const TArray<FHitResult>& HitResults, const float AttackTime)
{
	// If Client Skill Activate Succeed, but Server Activate Failed (cause NetworkDelay, etc...)
	// Pass Validate. But Implementation Function will return without doing anything
	if (CurrentSkillIndex == -1)
	{
		return;
	}
	
	float AttackDamage = SkillOwnerCharacter->GetAttackDamage();
	for (auto& HitResult : HitResults)
	{
		HitResult.GetActor()->TakeDamage(AttackDamage, FDamageEvent(), OwnerCharacter->GetController(), OwnerCharacter);
	}
}

bool UFMSkillComponent::ServerSweepAttack_Validate(const TArray<FHitResult>& HitResults, const float AttackTime)
{
	// If Client Skill Activate Succeed, but Server Activate Failed (cause NetworkDelay, etc...)
	// Pass Validate. But Implementation Function will return without doing anything
	if (CurrentSkillIndex == -1)
	{
		return true;
	}
	
	// Get Current AnimSequence
	UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
	
	TArray<FAnimNotifyEvent> Notifies = CurrentMontage->Notifies;
	float TimeDiff = AttackTime - AttackStartTime;
	for (auto& Notify : Notifies)
	{
		if (Notify.NotifyName == SweepAttackName)
		{
			// Notifies are called Tick after TriggerTime
			// So Calculate by adding a NotifyTriggerThreshold
			if (TimeDiff >= Notify.GetTriggerTime() || TimeDiff < Notify.GetEndTriggerTime() + NotifyTriggerThreshold)
			{
				return true;
			}
		}
	}
	
	return false;
}
