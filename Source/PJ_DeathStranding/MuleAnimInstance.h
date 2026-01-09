// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Mule.h"
#include "MuleAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PJ_DEATHSTRANDING_API UMuleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	EMuleState CurrentState;
};
