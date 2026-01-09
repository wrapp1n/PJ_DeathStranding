// Fill out your copyright notice in the Description page of Project Settings.


#include "Mule.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMule::AMule()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMule::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMule::SetState(EMuleState NewState)
{
	CurrentState = NewState;
}


void AMule::DoDead()
{
	//FName SectionName = FName(FString::Printf(TEXT("%d"), FMath::RandRange(1, 6)));

}

void AMule::DoDeadEnd()
{
	GetController()->SetActorEnableCollision(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AMule::ChangeSpeed(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;

}


