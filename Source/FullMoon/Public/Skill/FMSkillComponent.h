// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMPlayerSkillData.h"
#include "FMSkillBase.h"
#include "Components/ActorComponent.h"
#include "DataStructure/FMPriorityList.h"
#include "FMSkillComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFMSkillComponent, Log, All);

class UFMSkillBase;
class IFMCharacterSkillInterface;

USTRUCT(BlueprintType)
struct FFMSkillData
{
	GENERATED_BODY()

public:
	FFMSkillData()
		: bCanActivate(true)
	{
	}

	explicit FFMSkillData(UFMSkillBase* NewSkillBase)
		: SkillData(NewSkillBase)
		, bCanActivate(true)
	{
	}

public:
	FORCEINLINE UFMSkillBase* GetSkillData() const { return SkillData; }
	FORCEINLINE void SetSkillData(UFMSkillBase* NewSkillBase) { SkillData = NewSkillBase; }
	
	FORCEINLINE bool CanActivate() const { return bCanActivate; }
	FORCEINLINE void SetCanActivate(bool NewBool) { bCanActivate = NewBool; }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	TObjectPtr<UFMSkillBase> SkillData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	uint8 bCanActivate : 1;
	
};

struct FFMSkillCoolDownData
{
public:
	FFMSkillCoolDownData()
	{
	}

	FFMSkillCoolDownData(int32 NewIndex, float NewCoolDown)
		: SkillIndex(NewIndex), SkillCoolDown(NewCoolDown)
	{
	}

public:
	bool operator<(const FFMSkillCoolDownData& SkillCoolDownData) const
	{
		if (SkillCoolDown < SkillCoolDownData.SkillCoolDown)
		{
			return true;
		}
		
		return false;
	}

public:
	int32 SkillIndex = 0;
	float SkillCoolDown = 0.0f;
};

struct FFMBoneInfo
{
public:
	FFMBoneInfo()
		: BoneIndex(0)
	{
	}

	FFMBoneInfo(FName NewName, int32 NewIndex)
		: BoneName(NewName), BoneIndex(NewIndex)
	{
	}

public:
	FName BoneName;
	int32 BoneIndex;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FULLMOON_API UFMSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFMSkillComponent();

	virtual void InitializeComponent() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	TObjectPtr<ACharacter> OwnerCharacter;
	IFMCharacterSkillInterface* SkillOwnerCharacter;

public:
	UFUNCTION(Server, Reliable)
	void ServerActivateSkill(const EPlayerSkillCategory SkillCategory);
	
	bool ActivateSkill(const EPlayerSkillCategory SkillCategory);

	void FinishedActivateSkill();
	void FailedActivateSkill();
	
public:
	FORCEINLINE TArray<FFMSkillData>& GetAllSkills() { return Skills; }
	FORCEINLINE const FFMSkillData& GetSkill(EPlayerSkillCategory SkillCategory) const { return Skills[static_cast<int32>(SkillCategory)]; }
	FORCEINLINE void ClearSkills() { Skills.Empty(); }

	FORCEINLINE int32 GetCurrentSkillIndex() const { return CurrentSkillIndex; }

	void InitSkills();
	void AddSkill(UFMSkillBase* Skill);

protected:
	// Skill Data Array
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	TArray<FFMSkillData> Skills;

	// Skill CoolDown Array for UI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	TArray<float> SkillCoolDowns;

	// Skill CoolDown List Calculated In Server
	TFMPriorityList<FFMSkillCoolDownData> CoolDownList;
	float ElapsedTime = 0.0f;
	
	/**
	 * Used to check whether a skill is enabled.
	 * if CurrentSkillIndex == -1, no skills are active.
	 */
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	int32 CurrentSkillIndex = -1;

protected:
	void HitStop(float NewPlayRate, float Duration);

// Sweep Attack
public:
	void SweepAttack(const FVector& StartLocation, const FVector& EndLocation, float Radius, ECollisionChannel CollisionChannel, bool bIsStart, bool bIsEnd,
		const FTransform& FirstSocketLocalTransform, const FTransform& SecondSocketLocalTransform, FName WeaponSocketName);

protected:
	const FName LeafBone = TEXT("hand_r");
	const FName RootBone = TEXT("root");

	FTransform PrevMeshTransform;
	FVector PrevLocation;
	FVector PrevDirection;
	float PrevTime = 0.0f;
	
	TSet<TObjectPtr<AActor>> HitResultSet;
	TArray<FFMBoneInfo> ParentBones;

	void SweepCollisionDetection(const FVector& StartLocation, const FVector& EndLocation, float Radius, ECollisionChannel CollisionChannel);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSweepAttack(const TArray<FHitResult>& HitResults);
	
};
