// Fill out your copyright notice in the Description page of Project Settings.


#include "Sam_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"




// Sets default values
ASam_Character::ASam_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetGenericTeamId(1);

}

// Called when the game starts or when spawned
void ASam_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASam_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASam_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Sprint, ETriggerEvent::Started, this,
			&ASam_Character::StartSprint);
		UIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this,
			&ASam_Character::StopSprint);
	}

}

void ASam_Character::Move(float Forward, float Right)
{
	const FRotator CameraRotation = GetController()->GetControlRotation();
	const FRotator YawRotation = FRotator(0, CameraRotation.Yaw, 0);
	const FRotator YawRollRotation = FRotator(0, CameraRotation.Yaw, CameraRotation.Roll);


	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);
	AddMovementInput(ForwardVector, Forward);

	const FVector RightVector = UKismetMathLibrary::GetRightVector(YawRollRotation);
	AddMovementInput(RightVector, Right);
}

void ASam_Character::Look(float Pitch, float Yaw)
{
	AddControllerPitchInput(Pitch);
	AddControllerYawInput(Yaw);
}

void ASam_Character::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ASam_Character::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

}

void ASam_Character::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamID = InTeamID;
}

FGenericTeamId ASam_Character::GetGenericTeamId() const
{
	return TeamID;
}

FRotator ASam_Character::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();
	//	ActorToWorld().InverseTransformVectorNoScale(GetBaseAimRotation().Vector()).Rotation();
	return AimRotLS;
}

