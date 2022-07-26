// Fill out your copyright notice in the Description page of Project Settings.


#include "HSAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AHSAIController::AHSAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/BT_HSMonster.BT_HSMonster'"));
	if (BT.Succeeded())
	{
		_behaviorTree = BT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/AI/BB_HSMonster.BB_HSMonster'"));
	if (BD.Succeeded())
	{
		_blackboardData = BD.Object;
	}
}

void AHSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//GetWorld()->GetTimerManager().SetTimer(_timerHandle, this,&AHSAIController::RandomMove, 3.f, true);

	if (UseBlackboard(_blackboardData, Blackboard))
	{
		if (RunBehaviorTree(_behaviorTree))
		{

		}
	}
}

void AHSAIController::OnUnPossess()
{
	Super::OnUnPossess();

	//GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void AHSAIController::RandomMove()
{
	auto currentPawn = GetPawn();

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (navSystem == nullptr)
		return;

	FNavLocation randomLocation;

	if (navSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, randomLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randomLocation);
	}
}
