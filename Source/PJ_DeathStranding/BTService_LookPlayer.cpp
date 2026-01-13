// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LookPlayer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Mule.h"

UBTService_LookPlayer::UBTService_LookPlayer()
{
	NodeName = TEXT("LookPlayer");

}


void UBTService_LookPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (Player)
	{
		AActor* Mule = OwnerComp.GetAIOwner()->GetPawn();
		FVector MuleLocation = Mule->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(
			MuleLocation,
			PlayerLocation
		);

		LookRotation.Pitch = 0;

		FRotator TargetRotation = FMath::RInterpTo(Mule->GetActorRotation(),
			LookRotation, DeltaSeconds, 15.0f);

		Mule->SetActorRotation(TargetRotation);

	}
}
