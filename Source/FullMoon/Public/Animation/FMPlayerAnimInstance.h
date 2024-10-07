// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FMPlayerAnimInstance.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class FULLMOON_API UFMPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFMPlayerAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<ACharacter> CharacterOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float Direction = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float Speed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float MoveThreshold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsInAir : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	float JumpThreshold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsDead : 1;
	
};
