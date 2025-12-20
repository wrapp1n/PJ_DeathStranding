// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Sam_Character.h"
#include "Sam_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PJ_DEATHSTRANDING_API USam_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float GroundSpeed = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bSprint : 1;

	UFUNCTION()
	void AnimNotify_SkeletonNotify();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float Direction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float AimYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float AimPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsCrouched : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	FRotator AimRotation;
};
