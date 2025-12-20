// Fill out your copyright notice in the Description page of Project Settings.


#include "Sam_AnimInstance.h"
#include "Sam_Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"


void USam_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ASam_Character* Character = Cast<ASam_Character>(TryGetPawnOwner());
	if (Character)
	{
		GroundSpeed = Character->GetCharacterMovement()->Velocity.Size2D();
		bSprint = Character->bSprint;
		Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetCharacterMovement()->Velocity, Character->GetActorRotation());
		AimYaw = Character->GetAimOffset().Yaw;
		AimPitch = Character->GetAimOffset().Pitch;
		

		bIsCrouched = Character->bIsCrouched;

		bIsFalling = Character->GetCharacterMovement()->IsFalling();

	}
}

void USam_AnimInstance::AnimNotify_SkeletonNotify()
{
}
