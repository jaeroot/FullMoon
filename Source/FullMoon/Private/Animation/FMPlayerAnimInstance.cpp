// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FMPlayerAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UFMPlayerAnimInstance::UFMPlayerAnimInstance()
{
	MoveThreshold = 5.0f;
	JumpThreshold = 100.0f;
	
	bIsIdle = true;
	bIsInAir = false;
	bIsJumping = false;
	bIsDead = false;
}

void UFMPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CharacterOwner = Cast<ACharacter>(GetOwningActor());
	if (IsValid(CharacterOwner))
	{
		MovementComponent = CharacterOwner->GetCharacterMovement();
	}
}

void UFMPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (IsValid(MovementComponent))
	{
		Velocity = MovementComponent->Velocity;
		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, CharacterOwner->GetActorRotation());
		Speed = Velocity.Size2D();
		bIsIdle = Speed < MoveThreshold;
		bIsInAir = MovementComponent->IsFalling();
		bIsJumping = bIsInAir & (Velocity.Z > JumpThreshold);
	}
}
