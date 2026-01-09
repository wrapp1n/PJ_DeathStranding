// Fill out your copyright notice in the Description page of Project Settings.


#include "MuleAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


void UMuleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMule* Mule = Cast<AMule>(TryGetPawnOwner());
	if (Mule)
	{
		Speed = Mule->GetCharacterMovement()->Velocity.Size2D();
		CurrentState = Mule->CurrentState;
	}
}
