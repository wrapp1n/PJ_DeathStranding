// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mule.generated.h"

UENUM(BlueprintType)
enum class EMuleState : uint8
{
	Patrol = 0 UMETA(DisplayName = "Patrol"),
	Chase = 1 UMETA(DisplayName = "Chase"),
	Battle = 2 UMETA(DisplayName = "Battle"),
	Death = 3 UMETA(DisplayName = "Death")
};

UCLASS()
class PJ_DEATHSTRANDING_API AMule : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMule();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EMuleState CurrentState;

	void SetState(EMuleState NewState);

	UFUNCTION(BlueprintCallable)
	void DoDead();

	UFUNCTION(BlueprintCallable)
	void DoDeadEnd();

	UFUNCTION(BlueprintCallable)
	void ChangeSpeed(float NewMaxSpeed);

	FORCEINLINE const EMuleState GetCurrentState() { return CurrentState; }


};
