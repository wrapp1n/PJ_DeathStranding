// Fill out your copyright notice in the Description page of Project Settings.


#include "Mule_AIC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Sam_Character.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Mule.h"


AMule_AIC::AMule_AIC()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 800.0f;
	Sight->LoseSightRadius = 900.0f;
	Sight->PeripheralVisionAngleDegrees = 45.f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());



}

void AMule_AIC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//ensure(RunBTAsset); //Log
	//check(RunBTAsset); //우선 종료 후 로그 확인
	if (RunBTAsset)
	{
		RunBehaviorTree(RunBTAsset);
	}

	//Perception->OnPerceptionUpdated.AddDynamic(this, &AZombie_AIC::ProcessPerception);
	//Perception->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AZombie_AIC::ProcessActorPerceptionInfo);
	Perception->OnTargetPerceptionForgotten.AddDynamic(this, &AMule_AIC::ProcessPerceptionForget);
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AMule_AIC::ProcessActorPerception);
	SetGenericTeamId(3);
}

void AMule_AIC::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMule_AIC::ProcessPerception(const TArray<AActor*>& UpdatedActors)
{
	for (auto Actor : UpdatedActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("ProcessPerception %s"), *Actor->GetName());
	}
}

void AMule_AIC::ProcessActorPerception(AActor* Actor, FAIStimulus Stimulus)
{
	//UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerception %s %s"), *Actor->GetName() ,
	//	*Stimulus.Type.Name.ToString());

	//시야
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		if (Stimulus.WasSuccessfullySensed()) //봤을때
		{
			//UE_LOG(LogTemp, Warning, TEXT("Type Sight"));

			ASam_Character* Player = Cast<ASam_Character>(Actor);
			AMule* Mule = Cast<AMule>(GetPawn());
			if (Player && Mule)
			{
				if (Mule->GetCurrentState() == EMuleState::Death)
				{
					return;
				}

				Blackboard->SetValueAsObject(TEXT("Target"), Player);
				SetState(EMuleState::Chase);
				Mule->SetState(EMuleState::Chase);
				Mule->ChangeSpeed(400.0f);
			}
		}
		else // 못봤을때
		{
			ASam_Character* Player = Cast<ASam_Character>(Actor);
			AMule* Mule = Cast<AMule>(GetPawn());
			if (Player && Mule)
			{
				if (Mule->GetCurrentState() == EMuleState::Death)
				{
					return;
				}

				Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
				//Blackboard->SetValueAsVector(TEXT("Destination"), Stimulus.StimulusLocation);
				SetState(EMuleState::Patrol);
				Mule->SetState(EMuleState::Patrol);
				Mule->ChangeSpeed(150.0f);
			}
		}
	}

}

void AMule_AIC::ProcessPerceptionForget(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionForget %s"), *Actor->GetName());

	//아까 본데 까먹으면 
	ASam_Character* Player = Cast<ASam_Character>(Actor);
	AMule* Mule = Cast<AMule>(GetPawn());
	if (Player && Mule)
	{
		if (Mule->GetCurrentState() == EMuleState::Death)
		{
			return;
		}

		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
		SetState(EMuleState::Patrol);
		Mule->SetState(EMuleState::Patrol);
		Mule->ChangeSpeed(150.0f);
	}

}

void AMule_AIC::ProcessActorPerceptionInfo(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionForget %s"), *(UpdateInfo.Target->GetName()));
}

void AMule_AIC::SetState(EMuleState NewState)
{
	Blackboard->SetValueAsEnum(TEXT("CurrentState"), (uint8)(NewState));
}