// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FMPlayerCharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogFMCharacter, Log, All);

UCLASS()
class FULLMOON_API AFMPlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AFMPlayerCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Input Actions
protected:
	// Base Free Move Input Action Functions
	void FreeMove(const FInputActionValue& Value);
	void FreeLook(const FInputActionValue& Value);
	void JumpAction();
	
protected:
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	// Animation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<UAnimInstance> AnimInstance;

// Default Linked Anim Layer
protected:
	UPROPERTY(VisibleAnywhere, Category = Animation, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UAnimInstance> DefaultLinkedAnimLayer;
	
};
